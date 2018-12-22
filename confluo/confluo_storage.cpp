//
// Created by root on 18-12-22.
//
#include <iostream>
#include <string>
#include "confluo_store.h"

/**
 * test confluo performance
 *
 **/
int main(){
    confluo::confluo_store store("/export/confluo/data");
    std::string schema = "{timestamp: ULONG,op_latency_ms: DOUBLE,cpu_util: DOUBLE,mem_avail: DOUBLE,log_msg: STRING(100)}";

    auto storage_mode = confluo::storage::IN_MEMORY;
    store.create_atomic_multilog("perf_log", schema, storage_mode);
    confluo::atomic_multilog* mlog = store.get_atomic_multilog("perf_log");
    mlog->add_index("op_latency_ms");
    size_t off1 = mlog->append({"100", "0.5", "0.9",  "INFO: Launched 1 tasks"});
    size_t off2 = mlog->append({"500", "0.9", "0.05", "WARN: Server {2} down"});
    size_t off3 = mlog->append({"1001", "0.9", "0.03", "WARN: Server {2, 4, 5} down"});
    std::cout<<mlog->num_records()<<std::endl;
   /* auto record_stream = mlog->query_filter("low_resources", 0, UINT64_MAX);
    for (auto s = record_stream; !s.empty(); s = s.tail()) {
        std::cout << s.head().to_string();
    }*/
}

