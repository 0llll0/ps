// [프로그래밍 스튜디오 03분반]
// 2-2. 비만 판정 문제
// 22400315 박형찬

#include <stdio.h>

int main() {
    int height, weight;
    float bmi;

    scanf("%d %d", &height, &weight);

    bmi = weight / ((height / 100.0) * (height / 100.0));

    if (bmi >= 25)
        printf("Yes");
    else
        printf("No");

    return 0;
}