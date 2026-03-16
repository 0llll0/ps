#include <stdio.h>

int main() {
    float score[10];
    float max, min, total = 0, average;
    int i;

    for (i = 0; i < 10; i++) {
        scanf("%f", &score[i]);
    }

    max = score[0];
    min = score[0];

    for (i = 0; i < 10; i++) {
        if (score[i] > max)
            max = score[i];
        if (score[i] < min)
            min = score[i];
        total += score[i];
    }

    average = (total - max - min) / 8;

    printf("%.1f", average);

    return 0;
}