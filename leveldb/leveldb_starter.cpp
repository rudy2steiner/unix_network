//
// Created by root on 18-10-5.
//

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string>
// 包含必要的头文件
#include <leveldb/db.h>
/**
 * 静态链接
 * g++ -std=c++11 leveldb_starter.cpp -I /home/workspace/leveldb/include/ -o starter libleveldb.a -lpthread
 * ar -t libleveldb.a
 **/
using namespace std;

int main(void)
{
    leveldb::DB *db = nullptr;
    leveldb::Options options;

    // 如果数据库不存在就创建
    options.create_if_missing = true;

    // 创建的数据库在 /tmp/testdb
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    assert(status.ok());

    std::string key = "A";
    std::string value = "a";
    std::string get_value;

    // 写入 key1 -> value1
    leveldb::Status s = db->Put(leveldb::WriteOptions(), key, value);

    // 写入成功，就读取 key:people 对应的 value
    if (s.ok())
        s = db->Get(leveldb::ReadOptions(), "A", &get_value);

    // 读取成功就输出
    if (s.ok())
        cout << get_value << endl;
    else
        cout << s.ToString() << endl;

    delete db;

    return 0;
}