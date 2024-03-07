int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize){
    int total = 0; // 可以加的所有汽油之和
    int current = 0; // 当前邮箱的汽油
    int i;
    int start = 0;

    for (i = 0; i < gasSize; i++) {
        total += gas[i] - cost[i];
        current += gas[i] - cost[i];
        // 如果当前邮箱中的汽油无法到达下一个加油站，从下一个加油站重新开始
        if (current < 0) {
            current = 0;
            start = i + 1;
        } 
    }

    // 如果加油站汽油之和 小于 要消耗的汽油之和， 肯定无法绕一圈
    if (total < 0) {
        return -1;
    }

    return start;
}