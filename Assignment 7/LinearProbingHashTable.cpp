#include "LinearProbingHashTable.h"
using namespace std;


LinearProbingHashTable::LinearProbingHashTable(HashFunction<string> hashFn) {
    HashFFFFn = hashFn;
    elems = new Slot[hashFn.numSlots()];
    for (int i = 0; i < hashFn.numSlots(); i++)
    {
        elems[i].type = SlotType::EMPTY;
        elems[i].value = "57+g5pif55+z";
    }
    array_size = hashFn.numSlots();
}

LinearProbingHashTable::~LinearProbingHashTable() {
    delete[] elems;
    elems = nullptr; // 不知怎的，一旦delete()，程序就会崩溃，最后再来实现他 ———— 知道问题所在了，你忘记写[]了。siyuan://blocks/20240811084525-3izzoll
}

int LinearProbingHashTable::size() const {
    return actual_size; // 重点在于，你得维护一个int size变量，每当你insert()一次，actual_size就++
}

bool LinearProbingHashTable::isEmpty() const {
    if (actual_size == 0){
        cout << "Table is empty!" << endl;
        return true;
    }else{
        return false;
    }
}

bool LinearProbingHashTable::insert(const string& elem) {
    if (contains(elem))
    {return false;}

    int hash_code = HashFFFFn(elem); // 先计算出elem的hash code;
    if (elems[hash_code].value == elem)
    {return false;}

    if(isFull() == false){
        if (elems[hash_code].type == SlotType::EMPTY
            || elems[hash_code].type == SlotType::TOMBSTONE)
        {
            elems[hash_code].value = elem;
            elems[hash_code].type = SlotType::FILLED;
            actual_size++;
            return true;
        } else {
            int i = hash_code;
            i++;
            if (i == array_size){
                i = 0;
            }
            while(elems[i].type == SlotType::FILLED){
                i++;
                if (i == array_size){
                    i = 0;
                }
            }
            elems[i].value = elem;
            elems[i].type = SlotType::FILLED;
            actual_size++;
            // printDebugInfo();
            return true;
        }
    }else{
        // printDebugInfo();
        return false;
    }
}

bool LinearProbingHashTable::contains(const string& elem) const {
    int hash_code = HashFFFFn(elem);
    int i = hash_code;

    while (true) {
        // 如果找到一个空槽，说明元素不在表中
        if (elems[i].type == SlotType::EMPTY) {
            return false;
        }

        // 如果找到了匹配的元素，返回 true
        if (elems[i].type == SlotType::FILLED && elems[i].value == elem) {
            return true;
        }

        // 如果元素不存在或者是 TOMBSTONE，继续检查下一个位置
        i++;
        if (i == array_size) { // 到达数组边界，循环到数组头部
            i = 0;
        }

        // 如果回到起始位置，说明已经查找了整个表
        if (i == hash_code) {
            return false;
        }
    }
}


bool LinearProbingHashTable::remove(const string& elem) {
    // 我想要逻辑删除某个元素，把他标记成tombstone;
    // if(contains(elem))
    // {
    //     // 说明找到了对应的元素;
    //     elems[location].type = SlotType::TOMBSTONE;
    //     actual_size--;
    //     return true;
    // }else{
    //     return false;
    // }
    /* 关于location变量，我认为一点点耦合是有益的，可惜题目不允许 */

    // if(!contains(elem)){
    //     return false; // 不要去试图找一个不存在的东西了
    // }

    int hash_code = HashFFFFn(elem);
    if (elems[hash_code].type == SlotType::EMPTY) { // 如果一开始就是empty，那么hashcode后面的格子就什么都没有，也不用继续找了
        return false;
    }
    if (elems[hash_code].value == elem && elems[hash_code].type != SlotType::TOMBSTONE){
        // 说明找到了对应的元素;
        elems[hash_code].type = SlotType::TOMBSTONE;
        actual_size--;
        return true;
    } else {
        int i = hash_code;
        while(true)
        {
            i++;
            if (i == array_size){
                i = 0;
            }
            if (elems[i].type == SlotType::EMPTY) { // 如果某个格子是empty，那么后面就什么都没有，我们可以直接提前终止
                return false;
            }
            if (elems[i].value == elem // 如果转了一圈找到了，那就return TRUE;
                && elems[i].type != SlotType::TOMBSTONE)
            {
                elems[i].type = SlotType::TOMBSTONE;
                actual_size--;
                return true;
            }

            if (i == hash_code){ // 如果转了一圈还没找到，那就return false;
                return false;
            }
        }
    }
}

/*
我们还强烈建议以打印表内容的方式实现 printDebugInfo()，标记哪些槽为空，哪些槽为非空。这对你以后会有帮助。
*/
void LinearProbingHashTable::printDebugInfo() const {
    for(int i = 0; i < array_size; i++)
    {
        cout << i << " ";
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    
    for(int i = 0; i < array_size; i++)
    {
        cout << elems[i] << " ";
    }
    cout << endl;
}

bool LinearProbingHashTable::isFull(){
    if(actual_size == array_size)
    {
        return true; // 装满了
    }else{
        return false;
    }
}

// bool LinearProbingHashTable::printDebugInfo(){
//     printDebugInfo();
//     return true;
// }

/* * * * * * Test Cases Below This Point * * * * * */
#include "GUI/SimpleTest.h"

/* Optional: Add your own custom tests here! */














/* * * * * Provided Tests Below This Point * * * * */
#include "vector.h"

PROVIDED_TEST("Table is initially empty.") {
    LinearProbingHashTable table(Hash::random(10));

    /* Check the external interface to make sure it looks good. */
    EXPECT_EQUAL(table.size(), 0);
    EXPECT(table.isEmpty());

    /* Check that, internally, all is well. */
    EXPECT_NOT_EQUAL(table.elems, nullptr);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }
}

PROVIDED_TEST("Can insert and look up a single value.") {
    LinearProbingHashTable table(Hash::identity(10));

    EXPECT(!table.contains("0"));
    EXPECT(table.insert("0"));
    EXPECT(table.contains("0"));

    /* Check internal representation. */
    EXPECT_EQUAL(table.elems[0], { "0", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }
}

PROVIDED_TEST("Is case-sensitive.") {
    LinearProbingHashTable table(Hash::zero(10));

    EXPECT(!table.contains("a"));
    EXPECT(!table.contains("A"));
    EXPECT(table.insert("a"));

    /* Should have 'a' in the first slot and otherwise be empty. */
    EXPECT_EQUAL(table.elems[0], { "a", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }

    EXPECT(table.contains("a"));
    EXPECT(!table.contains("A"));
}

PROVIDED_TEST("Insertions/lookups work with hash collisions.") {
    /* Use a very, very bad hash function that maps everything to slot zero. */
    LinearProbingHashTable table(Hash::zero(10));

    Vector<string> toAdd = {
        "Quokka", "Pudu", "Gerenuk", "Dikdik"
    };
    Vector<string> toNotAdd = {
        "Springbok", "Kudu"
    };

    for (string animal: toAdd) {
        EXPECT(table.insert(animal));
    }
    EXPECT_EQUAL(table.size(), toAdd.size());

    /* Should be 'Quokka', 'Pudu', 'Gerenuk', 'Dikdik', and then six blank slots. */
    for (int i = 0; i < 10; i++) {
        if (i < toAdd.size()) {
            EXPECT_EQUAL(table.elems[i], { toAdd[i], LinearProbingHashTable::SlotType::FILLED });
        } else {
            EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
        }
    }

    for (string animal: toAdd) {
        EXPECT(table.contains(animal));
    }
    for (string animal: toNotAdd) {
        EXPECT(!table.contains(animal));
    }
}

PROVIDED_TEST("Insertions/lookups succeed when ranges overlap.") {
     /* 我们使用的哈希函数将字符串映射到它们的数值。这允许我们控制哈希表的内容。*/
    LinearProbingHashTable table(Hash::identity(10));

     /* 插入 0 和 10。此时表应该如下所示：
     *
     *            0 10 . . . . . . . .
     *
     */
    EXPECT(table.insert("0"));
    EXPECT(table.insert("10"));
    EXPECT(table.contains("0"));
    EXPECT(table.contains("10"));

    EXPECT_EQUAL(table.elems[0], {  "0", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[1], { "10", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 2; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }

    /* 现在插入值 1、2、3、4 和 5。此时表应该如下所示：
     *
     *           0 10  1  2  3  4  5  .  .  .
     */
    EXPECT(table.insert("1"));
    EXPECT(table.insert("2"));
    EXPECT(table.insert("3"));
    EXPECT(table.insert("4"));
    EXPECT(table.insert("5"));

    EXPECT_EQUAL(table.elems[0], {  "0", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[1], { "10", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[3], {  "2", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[4], {  "3", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6], {  "5", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 7; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }

    /* 确保我们可以找到所有元素。*/
    EXPECT(table.contains("0"));
    EXPECT(table.contains("1"));
    EXPECT(table.contains("2"));
    EXPECT(table.contains("3"));
    EXPECT(table.contains("4"));
    EXPECT(table.contains("5"));
    EXPECT(!table.contains("6"));
    EXPECT(!table.contains("7"));
    EXPECT(!table.contains("8"));
    EXPECT(!table.contains("9"));
    EXPECT(table.contains("10"));

    EXPECT_EQUAL(table.size(), 7);
}

PROVIDED_TEST("Wraps around the end of the table.") {
    /* Everything goes in slot 7. This is a terrible hash function that's just used for
     * testing purposes.
     */
    LinearProbingHashTable table(Hash::constant(10, 7));

    /* Insert a bunch of values. */
    Vector<string> toAdd = {
        "H", "He", "Li", "Be", "B", "C", "N"
    };
    Vector<string> toNotAdd = {
        "O", "F", "Ne"
    };

    /* Add the elements in. */
    for (string elem: toAdd) {
        EXPECT(table.insert(elem));
    }

    /* Table should be
     *
     * Be B  C  N  .  .  .  H  He Li
     */
    EXPECT_EQUAL(table.elems[0], { "Be", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[1], { "B",  LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2], { "C",  LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[3], { "N",  LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[4].type,     LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[5].type,     LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[6].type,     LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[7], { "H",   LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[8], { "He",  LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[9], { "Li",  LinearProbingHashTable::SlotType::FILLED });

    /* Confirm they're all there. */
    for (string elem: toAdd) {
        EXPECT(table.contains(elem));
    }

    /* Confirm others aren't. */
    for (string elem: toNotAdd) {
        EXPECT(!table.contains(elem));
    }
}

PROVIDED_TEST("Doesn't allow for duplicates.") {
    /* Drop everything into slot zero, just for consistency. */
    LinearProbingHashTable table(Hash::zero(10));

    EXPECT(table.insert("Dikdik"));
    EXPECT_EQUAL(table.size(), 1);

    /* Insert the same value more times than the table can hold. */
    for (int i = 0; i < 100; i++) {
        EXPECT(!table.insert("Dikdik"));
        EXPECT_EQUAL(table.size(), 1);
    }

    EXPECT_EQUAL(table.elems[0], { "Dikdik", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }
}

PROVIDED_TEST("Handles inserting the empty string.") {
    LinearProbingHashTable table(Hash::zero(10));

    EXPECT(!table.contains(""));
    EXPECT(table.insert(""));
    EXPECT(table.contains(""));
    EXPECT_EQUAL(table.size(), 1);

    EXPECT_EQUAL(table.elems[0], { "", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }
}

PROVIDED_TEST("Lookups work even if the table is full.") {
    /* Dump everything in bucket 7. This is a terrible hash function, but it's
     * useful for testing.
     */
    LinearProbingHashTable table(Hash::constant(10, 7));

    /* Fill the table. */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i)));
    }

    /* Validate that the table has the shape we expect it to have. */
    EXPECT_EQUAL(table.size(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[(i + 7) % 10], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
    }

    /* Search for all present items. */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.contains(to_string(i)));
    }

    /* Confirm elements that aren't there don't show up. Watch out! This edge
     * case might cause your code to hang if you haven't anticipated it.
     */
    for (int i = 10; i < 20; i++) {
        EXPECT(!table.contains(to_string(i)));
    }
}

PROVIDED_TEST("Won't insert elements if table is full.") {
    /* Terrible hash function that places everything in slot zero. */
    LinearProbingHashTable table(Hash::zero(10));

    /* Load the table. */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i))); // Should succeed
    }

    /* Validate that the table has the shape we expect it to have. */
    EXPECT_EQUAL(table.size(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
    }

    /* All these operations should fail. */
    for (int i = 10; i < 20; i++) {
        EXPECT(!table.insert(to_string(i)));
    }

    /* Confirm the table wasn't modified. */
    EXPECT_EQUAL(table.size(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
    }
}

PROVIDED_TEST("Stress Test: Handles pure insertion of elements (should take at most three seconds).") {
    const int kNumTrials = 50; // 进行多次测试，以发现潜在的错误。
    for (int trial = 0; trial < kNumTrials; trial++) {
        LinearProbingHashTable table(Hash::random(100));

        const int kNumElems = 75;
        for (int i = 0; i < kNumElems; i++) {
            /* 确认此时仅包含正确的元素。 */
            for (int j = 0; j < kNumElems; j++) {
                EXPECT_EQUAL(table.contains(to_string(j)), bool(j < i));
            }

            /* 添加元素。 */
            EXPECT(table.insert(to_string(i))); // Should succeed
            EXPECT_EQUAL(table.size(), i + 1);
        }
    }
}

PROVIDED_TEST("Stress Test: Inserts/searches work in expected time O(1) (should take at most three seconds).") {
    /* Huge number of slots. */
    const int kNumSlots = 1000000;

    /* Create an enormous hash table with a random hash function. */
    LinearProbingHashTable table(Hash::random(kNumSlots));

    /* Search the table for lots of elements. This should quick, since
     * the table is empty.
     */
    for (int i = 0; i < kNumSlots; i++) {
        EXPECT(!table.contains(to_string(i)));
    }

    /* Insert a lot elements. */
    const int kLotsOfElems = 100000; // 10% load factor - quite small!
    for (int i = 0; i < kLotsOfElems; i++) {
        EXPECT(table.insert(to_string(i)));
    }
    for (int i = 0; i < kLotsOfElems; i++) {
        EXPECT(table.contains(to_string(i)));
    }

    /* Confirm other elements aren't there. These false lookups should still be fast
     * due to the low load factor.
     */
    for (int i = kLotsOfElems; i < 2 * kLotsOfElems; i++) {
        EXPECT(!table.contains(to_string(i)));
    }
}

PROVIDED_TEST("Can insert and remove a single element.") {
    /* Bad hash function mapping each string to the number it represents. */
    LinearProbingHashTable table(Hash::zero(10));

    /* Insert an element. */
    EXPECT(table.insert("137"));
    EXPECT_EQUAL(table.size(), 1);
    EXPECT(!table.isEmpty());

    /* Validate the table has the right shape. */
    EXPECT_EQUAL(table.elems[0], { "137", LinearProbingHashTable::SlotType::FILLED });
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }

    /* Remove the element. */
    EXPECT(table.remove("137"));
    EXPECT_EQUAL(table.size(), 0);
    EXPECT(table.isEmpty());

    /* Validate the table has the right shape. */
    EXPECT_EQUAL(table.elems[0].type, LinearProbingHashTable::SlotType::TOMBSTONE);
    for (int i = 1; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::EMPTY);
    }

    /* Confirm the lookup fails. */
    EXPECT(!table.contains("137"));
}

PROVIDED_TEST("Handles a single tombstone.") {
    /* Hash function mapping each item to its numeric position, which makes the test
     * predictably control where elements go.
     */
    LinearProbingHashTable table(Hash::identity(10));

    /* Inserting these values makes the table look like this:
     *
     *  .  1  2  3 13  5  .  .  .  .
     */
    EXPECT(table.insert("1"));
    EXPECT(table.insert("2"));
    EXPECT(table.insert("3"));
    EXPECT(table.insert("13"));
    EXPECT(table.insert("5"));
    EXPECT_EQUAL(table.size(), 5);

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[1], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2], {  "2", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[3], {  "3", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[4], { "13", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::EMPTY);

    /* Delete 3 from the table. We should now have this, where T
     * is a tombstone.
     *
     *    .  1  2  T 13  5  .  .  .  .
     */
    EXPECT(table.remove("3"));
    EXPECT_EQUAL(table.size(), 4);

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[1], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2], {  "2", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[4], { "13", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::EMPTY);

    /* Confirm everything else is still there. Note that if 13
     * is missing, there's a chance we aren't scanning over the
     * tombstone slot, and if 5 is missing it might mean that we
     * tried pulling previous elements backwards, which isn't
     * safe.
     */
    EXPECT(table.contains("1"));
    EXPECT(table.contains("2"));
    EXPECT(!table.contains("3"));
    EXPECT(table.contains("13"));
    EXPECT(table.contains("5"));
}


PROVIDED_TEST("Handles lookups with long chains of tombstones") {
    /* Hash function mapping each item to its numeric position, which makes the test
     * predictably control where elements go.
     */
    LinearProbingHashTable table(Hash::identity(10));

    /* Form this pattern:
     *
     * T 1 . . 4 5 T T T T
     */
    EXPECT(table.insert("4"));
    EXPECT(table.insert("5"));
    EXPECT(table.insert("6"));
    EXPECT(table.insert("7"));
    EXPECT(table.insert("8"));
    EXPECT(table.insert("9"));
    EXPECT(table.insert("0"));
    EXPECT(table.insert("1"));
    EXPECT(table.remove("6"));
    EXPECT(table.remove("7"));
    EXPECT(table.remove("8"));
    EXPECT(table.remove("9"));
    EXPECT(table.remove("0"));

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[1], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[4], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::TOMBSTONE);

    /* Confirm that 1, 4, and 5 are there. */
    EXPECT(table.contains("4"));
    EXPECT(table.contains("5"));
    EXPECT(table.contains("1"));

    /* Ensure nothing else is. */
    EXPECT(!table.contains("6"));
    EXPECT(!table.contains("7"));
    EXPECT(!table.contains("8"));
    EXPECT(!table.contains("9"));
    EXPECT(!table.contains("0"));

    EXPECT_EQUAL(table.size(), 3);
}

PROVIDED_TEST("Recycles space from tombstones.") {
    LinearProbingHashTable table(Hash::zero(10));

    /* Add ten values. */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i)));
    }
    EXPECT_EQUAL(table.size(), 10);

    /* Remove all of them. */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.remove(to_string(i)));
    }

    /* The table should now be empty, though each slot is now a tombstone. */
    EXPECT_EQUAL(table.size(), 0);
    EXPECT(table.isEmpty());
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::TOMBSTONE);
    }

    /* Add the elements a second time. If space for tombstones isn't recycled,
     * these operations will fail.
     */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i + 1000)));
        EXPECT_EQUAL(table.size(), i + 1);
    }

    /* Confirm the table has the right shape. */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i], { to_string(i + 1000), LinearProbingHashTable::SlotType::FILLED });
    }

    /* These operations should fail, because the table is now full. */
    for (int i = 10; i < 20; i++) {
        EXPECT(!table.insert(to_string(i)));
        EXPECT_EQUAL(table.size(), 10);
    }

    /* Confirm the preceding bit didn't change the table. */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i], { to_string(i + 1000), LinearProbingHashTable::SlotType::FILLED });
    }
}

PROVIDED_TEST("在墓碑位置上插入元素不会产生重复项。") {
    /* 哈希函数将所有项目映射到槽位4。这是一个非常糟糕的哈希函数，
     * 实际应用中不会有人使用，但在测试中非常方便！
     */
    LinearProbingHashTable table(Hash::constant(10, 4));

    /* Form this pattern:
     *
     * T 1 . . 4 5 T T T T
     */
    EXPECT(table.insert("4"));
    EXPECT(table.insert("5"));
    EXPECT(table.insert("6"));
    EXPECT(table.insert("7"));
    EXPECT(table.insert("8"));
    EXPECT(table.insert("9"));
    EXPECT(table.insert("0"));
    EXPECT(table.insert("1"));
    EXPECT(table.remove("6"));
    EXPECT(table.remove("7"));
    EXPECT(table.remove("8"));
    EXPECT(table.remove("9"));
    EXPECT(table.remove("0"));

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[1], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[4], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::TOMBSTONE);

    /* 向表中插入1。元素1已经存在，但要找到它，
     * 需要跳过墓碑槽位，尽管插入操作通常会
     * 覆盖墓碑槽位。
     */
    EXPECT(!table.insert("1"));
    EXPECT_EQUAL(table.size(), 3);

    /* 再次检查上一步测试后表中内容是否发生了变化。 */
    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[1], {  "1", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[2].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[4], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::TOMBSTONE);

    /* 确保不能删除两个副本的1。 */
    EXPECT(table.remove("1"));
    EXPECT_EQUAL(table.size(), 2);

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[1].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[2].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[4], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT(!table.remove("1")); // 你应该无法remove()成功，因为1已经被逻辑删除
    EXPECT_EQUAL(table.size(), 2);

    EXPECT_EQUAL(table.elems[0].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[1].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[2].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[3].type,    LinearProbingHashTable::SlotType::EMPTY);
    EXPECT_EQUAL(table.elems[4], {  "4", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[5], {  "5", LinearProbingHashTable::SlotType::FILLED });
    EXPECT_EQUAL(table.elems[6].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[7].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[8].type,    LinearProbingHashTable::SlotType::TOMBSTONE);
    EXPECT_EQUAL(table.elems[9].type,    LinearProbingHashTable::SlotType::TOMBSTONE);

    /* Confirm that 4 and 5 are still there. */
    EXPECT(table.contains("4"));
    EXPECT(table.contains("5"));

    /* Ensure nothing else is. */
    EXPECT(!table.contains("6"));
    EXPECT(!table.contains("7"));
    EXPECT(!table.contains("8"));
    EXPECT(!table.contains("9"));
    EXPECT(!table.contains("0"));
}

PROVIDED_TEST("Handles removing the empty string.") {
    LinearProbingHashTable table(Hash::random(10));

    EXPECT(!table.remove(""));

    EXPECT(!table.contains(""));
    EXPECT(table.insert(""));
    EXPECT(table.contains(""));
    EXPECT_EQUAL(table.size(), 1);

    EXPECT(table.remove(""));
    EXPECT_EQUAL(table.size(), 0);
    EXPECT(!table.contains(""));

    EXPECT(!table.remove(""));
}

PROVIDED_TEST("Can remove from a full table.") {
    /* Drop everything in bucket 7, which is a terrible choice of hash function but
     * which makes testing a lot easier.
     */
    LinearProbingHashTable table(Hash::constant(10, 7));

    /* Fill the table. */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.insert(to_string(i)));
    }
    EXPECT_EQUAL(table.size(), 10);

    /* Validate table internals. */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[(i + 7) % 10], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
    }

    /* Try removing some elements that aren't present. This may hang if your implementation
     * of remove wasn't anticipating this case.
     */
    for (int i = 10; i < 20; i++) {
        EXPECT(!table.remove(to_string(i)));
    }

    /* Validate table internals. */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[(i + 7) % 10], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
    }

    /* Now, do the actual removals. */
    for (int i = 0; i < 10; i++) {
        EXPECT(table.remove(to_string(i)));
    }
    EXPECT(table.isEmpty());
    EXPECT_EQUAL(table.size(), 0);

    /* Validate table internals. */
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL(table.elems[i].type, LinearProbingHashTable::SlotType::TOMBSTONE);
    }
}

PROVIDED_TEST("Stress Test: Handles large numbers of removals (should take at most three seconds).") {
    const int kNumTrials = 50; // Do this lots of times to smoke out any errors that might be lurking.
    for (int trial = 0; trial < kNumTrials; trial++) {
        LinearProbingHashTable table(Hash::random(100));

        const int kNumElems = 75;
        for (int i = 0; i < kNumElems; i++) {
            table.insert(to_string(i));
        }

        EXPECT_EQUAL(table.size(), kNumElems);

        for (int i = 0; i < kNumElems; i++) {
            /* Confirm only the proper elements exist at this point. */
            for (int j = 0; j < kNumElems; j++) {
                EXPECT_EQUAL(table.contains(to_string(j)), bool(j >= i));
            }

            EXPECT(table.remove(to_string(i)));
            EXPECT_EQUAL(table.size(), kNumElems - i - 1);
        }
    }
}

PROVIDED_TEST("Stress Test: Inserts/searches/deletes work in expected time O(1) (should take at most three seconds).") {
    /* Huge number of slots. */
    const int kNumSlots = 1000000;

    /* Create an enormous hash table with a random hash function. */
    LinearProbingHashTable table(Hash::random(kNumSlots));

    /* Insert a lot elements. */
    const int kLotsOfElems = 100000; // 10% load factor - quite small!
    for (int i = 0; i < kLotsOfElems; i++) {
        EXPECT(table.insert(to_string(i)));
    }

    /* Remove the middle half of them. */
    for (int i = kLotsOfElems / 4; i < 3 * kLotsOfElems / 4; i++) {
        EXPECT(table.remove(to_string(i)));
    }

    /* Search for lots of elements and confirm the ones are supposed to be there
     * are indeed there.
     */
    for (int i = 0; i < kLotsOfElems; i++) {
        EXPECT_EQUAL(table.contains(to_string(i)), bool(i < kLotsOfElems / 4 || i >= 3 * kLotsOfElems / 4));
    }
}

#include "filelib.h"
#include "Demos/Timer.h"
PROVIDED_TEST("Stress test: Core functions do not cause stack overflows (should take at most 15 seconds)") {
    // SHOW_ERROR("Stress test is disabled by default. To run it, comment out line " + to_string(__LINE__) + " of " + getTail(__FILE__) + ".");
    const int kTableSize = 1000000;

    /* Create a table with 1,000,000 slots, then fill in the first 999,999 of them. */
    Timing::Timer timer;
    timer.start();
    LinearProbingHashTable table(Hash::identity(kTableSize));
    for (int i = 0; i < kTableSize - 1; i++) {
        EXPECT(table.insert(to_string(i)));
    }

    /* Validate table. */
    EXPECT_EQUAL(table.size(), kTableSize - 1);
    for (int i = 0; i < kTableSize - 1; i++) {
        EXPECT_EQUAL(table.elems[i], { to_string(i), LinearProbingHashTable::SlotType::FILLED });
    }

    /* Insert the value 1,000,000. This wants to go into slot zero, but that's filled, so it will
     * scoot on over to the far end of the table to find the first free slot.
     */
    EXPECT(table.insert(to_string(kTableSize)));
    EXPECT_EQUAL(table.size(), kTableSize);
    EXPECT_EQUAL(table.elems[kTableSize - 1], { to_string(kTableSize), LinearProbingHashTable::SlotType::FILLED });

    /* Check if 1000000 is there, which requires scanning the whole table. */
    EXPECT(table.contains(to_string(kTableSize)));

    /* Remove 1000000, which requires scanning the whole table. */
    EXPECT(table.remove(to_string(kTableSize)));
    EXPECT_EQUAL(table.elems[kTableSize - 1].type, LinearProbingHashTable::SlotType::TOMBSTONE);
    timer.stop();

    EXPECT_LESS_THAN(timer.elapsed(), 15e9); // Measured in nanoseconds
}

#include <fstream>
PROVIDED_TEST("Stress Test: Handles large workflows with little free space (should take at most fifteen seconds)") {
    // SHOW_ERROR("Stress test is disabled by default. To run it, comment out line " + to_string(__LINE__) + " of " + getTail(__FILE__) + ".");

    Vector<string> english;
    ifstream input("res/EnglishWords.txt");

    for (string word; getline(input, word); ) {
        english += word;
    }

    /* Load factor 0.97. */
    Timing::Timer timer;
    timer.start();
    LinearProbingHashTable table(Hash::consistentRandom(english.size() / 0.97));

    /* Insert everything. */
    for (const string& word: english) {
        EXPECT(table.insert(word));
    }
    EXPECT_EQUAL(table.size(), english.size());

    /* Make sure everything is there, and that the upper-case versions aren't. */
    for (const string& word: english) {
        EXPECT(table.contains(word));
        EXPECT(!table.contains(toUpperCase(word)));
    }

    /* Remove everything, plus some things not there.. */
    for (const string& word: english) {
        EXPECT(table.remove(word));
        EXPECT(!table.contains(word));
        EXPECT(!table.remove(toUpperCase(word)));
    }

    EXPECT_EQUAL(table.size(), 0);
    EXPECT(table.isEmpty());

    timer.stop();
    EXPECT_LESS_THAN(timer.elapsed(), 15e9); // Measured in nanoseconds
}
