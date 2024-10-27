#include "scanner.h"
#include "network.h"
#include "global_data.h"
#include "utils.h"
#include "threads.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

static uint8_t get_port_state(uint32_t scan_type, uint8_t response)
{
    if (scan_type == SCAN_TYPE_SYN) {
        
        if (response == NO_RESPONSE)
            return PORT_STATE_FILTERED;
        if (response == TCP_SYN_ACK_PCKT)
            return PORT_STATE_OPEN;
        if (response == TCP_RST_PCKT)
            return PORT_STATE_CLOSED;
    }

    if (scan_type == SCAN_TYPE_ACK) {
        
        if (response == TCP_RST_PCKT)
            return PORT_STATE_UNFILTERED;
        return PORT_STATE_FILTERED;
    }

    if (scan_type == SCAN_TYPE_UDP) {
        
        if (response == NO_RESPONSE)
            return PORT_STATE_OPEN_FILTERED;
        if (response == ICMP_PCKT_T3_C3)
            return PORT_STATE_CLOSED;
        if (response == ICMP_PCKT_T3)
            return PORT_STATE_FILTERED;
        return PORT_STATE_OPEN;
    }

    if (scan_type == SCAN_TYPE_NULL || scan_type == SCAN_TYPE_FIN || scan_type == SCAN_TYPE_XMAS) {
        
        if (response == NO_RESPONSE)
            return PORT_STATE_OPEN_FILTERED;
        if (response == TCP_RST_PCKT)
            return PORT_STATE_CLOSED;
        return PORT_STATE_FILTERED;
    }

    return SCAN_TYPE_UNKNOWN;
}

static bool perform_port_scan(t_global_data *data, int32_t tcp_sockfd, int32_t udp_sockfd, sockaddr_in *dest, int16_t port, pcap_t *handle)
{
    uint32_t scan_types[NUM_SCAN_TYPE] = {
        SCAN_TYPE_SYN,
        SCAN_TYPE_FIN,
        SCAN_TYPE_NULL,
        SCAN_TYPE_XMAS,
        SCAN_TYPE_ACK,
        SCAN_TYPE_UDP,
    };

    for (uint8_t i = 0; i < NUM_SCAN_TYPE; i++) {
        bool packed_sended = false;

        if ((scan_types[i] == SCAN_TYPE_UDP) && (data->opts.scan_type & SCAN_TYPE_UDP)) {
            if (!send_udp_packet(data, udp_sockfd, dest, port))
                return false;

            packed_sended = true;
        } else if (data->opts.scan_type & scan_types[i]){
            if (!send_tcp_packet(data, tcp_sockfd, dest, port, scan_types[i]))
                return false;

            packed_sended = true;
        }

        if (!packed_sended)
            continue ;

        uint8_t scan_response = NO_RESPONSE; // memory error fixed, but wtf?
        if (!recv_packet(handle, &scan_response))
            return false;
        
        print_scan_line(
            data,
            port,
            scan_types[i],
            get_port_state(scan_types[i], scan_response)
        );
    }
    
    return true;
}

void *scan_port_range(void *args)
{
    t_thread_args *thread_args = (t_thread_args *)args;
    t_global_data *data = thread_args->data;
    int32_t tcp_socket = thread_args->tcp_sockfd;
    int32_t udp_socket = thread_args->udp_sockfd;
    sockaddr_in dest = thread_args->dest;
    uint16_t start_port_index = thread_args->start_port_index;
    uint16_t end_port_index = thread_args->end_port_index;

    pcap_t *handle = NULL;
    if (!pcap_initialization(&handle))
            goto exit_thread;

    for (uint16_t i = start_port_index; i <= end_port_index; i++) {
        uint16_t port = data->opts.ports[i];
        
        if (!set_pcap_filter(&handle, inet_ntoa(dest.sin_addr), port))
            goto exit_thread;

        if (!perform_port_scan(data, tcp_socket, udp_socket, &dest, port, handle))
            goto exit_thread;
    }
    
    goto exit_thread;

exit_thread:
    if (handle)
        pcap_close(handle);
    pthread_exit(NULL);
}

bool process_nmap_scans(t_global_data *data)
{
    int32_t tcp_sockfd = 0, udp_sockfd = 0;
    if (!open_tcp_sockfd(&tcp_sockfd) || !open_udp_sockfd(&udp_sockfd)) {
        cleanup_resources(data, tcp_sockfd, udp_sockfd);
        return false;
    }

    uint16_t n_threads = data->opts.speedup > data->opts.n_ports
                            ? data->opts.n_ports
                            : data->opts.speedup;
    
    pthread_t threads[n_threads];
    t_thread_args thread_args[n_threads];

    fprintf(data->opts.output, "[*] [SCANNING]");
    for (uint8_t addr_index = 0; data->opts.addr[addr_index]; addr_index++) {
        print_scan_ip_header(data, addr_index);

        sockaddr_in dest;
        memset(&dest, 0, sizeof(sockaddr_in));
        dest.sin_family = AF_INET;  
        dest.sin_addr.s_addr = inet_addr(data->opts.addr[addr_index]);

        uint16_t ports_per_thread = data->opts.n_ports / n_threads;
        uint16_t remainder_ports = data->opts.n_ports % n_threads;

        uint16_t curr_port_index = 0;
        for (uint16_t thread_index = 0; thread_index < n_threads; thread_index++) {
            initialize_thread_args(&thread_args[thread_index], data, tcp_sockfd, udp_sockfd,
                                        dest, thread_index, n_threads,
                                        &curr_port_index, ports_per_thread, remainder_ports);

            if (pthread_create(&threads[thread_index], NULL, scan_port_range, (void *)&thread_args[thread_index])) {
                cleanup_resources(data, tcp_sockfd, udp_sockfd);
                return false;
            }
        }
        
        for (uint8_t thread_index = 0; thread_index < n_threads ; thread_index++)
            pthread_join(threads[thread_index], NULL);
    }
    
    cleanup_resources(data, tcp_sockfd, udp_sockfd);
    return true;
}
