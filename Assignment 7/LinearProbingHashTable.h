#pragma once

#include "HashFunction.h"
#include "Demos/Utility.h"
#include "GUI/SimpleTest.h"
#include "GUI/MemoryDiagnostics.h"
#include <string>

class LinearProbingHashTable {
public:
    /**
     * 构造一个使用给定哈希函数的新线性探测表。
     * （注意，哈希函数允许你确定使用多少个槽；
     * 你可以通过调用 hashFn.numSlots() 来获取这个值。）
     */
    LinearProbingHashTable(HashFunction<std::string> hashFn);

    /**
     * 清理此哈希表分配的所有内存。
     */
    ~LinearProbingHashTable();

    /**
     * 返回表是否为空。
     */
    bool isEmpty() const;

    /**
     * 返回表中的元素数量。
     */
    int size() const;

    /**
     * 将指定元素插入到此哈希表中。如果该元素已经存在，
     * 则表保持不变，并返回 false 以表明没有添加任何内容。
     *
     * 如果表中没有插入元素的空间——即每个槽都已满——
     * 则应返回 false 以表明没有更多空间。
     *
     * 此函数返回元素是否已插入到表中。
     */
    bool insert(const std::string& key);

    /**
     * 返回表中是否包含指定键。
     */
    bool contains(const std::string& key) const;

    /**
     * 从此哈希表中移除指定元素。如果哈希表中不存在该元素，
     * 则此操作无效。
     *
     * 你应该使用墓碑删除来实现此操作——将包含该元素的槽标记为墓碑。
     *
     * 如果元素已被移除则返回 true，否则返回 false。
     */
    bool remove(const std::string& key);

    /**
     * 打印出相关信息以协助调试。
     */
    void printDebugInfo() const;

    bool isFull();

    // bool printDebugInfo();

private:
    /* 表示给定槽状态的类型。请不要修改此类型，
     * 因为我们的测试要求它完全按照当前的样子。
     */
    enum class SlotType {
        EMPTY, FILLED, TOMBSTONE
    };

    /* 表示线性探测表中槽的类型。请不要修改此类型，
     * 因为我们的测试要求它完全按照当前的样子。
     */
    struct Slot {
        std::string value;
        SlotType type;

        TRACK_ALLOCATIONS_OF(Slot);
    };

    /* 指向元素数组的指针。我们的测试期望你的实现使用
     * 'elems' 作为元素数组的指针名称，因此请不要重命名此变量。
     */
    Slot* elems = nullptr;

    /* TODO: 添加任何你希望的私有成员变量、成员函数或成员类型。
     * 只要你自己管理内存，不使用任何容器类型（如 Vector、HashSet 等），
     * 并使用带墓碑的线性探测，你可以按自己的意愿实现此类型。
     *
     * TODO: 提交前删除此注释。
     */
    HashFunction<std::string> HashFFFFn; // 用于计算hash code
    int actual_size = 0;
    int array_size = 0;
    // int location = 0; // 内部传递elem坐标




    /* Internal shenanigans to make this play well with C++. */
        /* 使其在 C++ 中很好运行的内部操作。 */
    DISALLOW_COPYING_OF(LinearProbingHashTable);
    ALLOW_TEST_ACCESS();
    MAKE_PRINTERS_FOR(SlotType);
    MAKE_PRINTERS_FOR(Slot);
    MAKE_COMPARATORS_FOR(Slot);
};
