#include <stdio.h>
#include <queue>
using namespace std;
 
struct SHARK {
    int y, x, time;
};
 
int n;
int map[20][20];
 
int shark_size, shark_eat;
SHARK shark;
 
const int dy[] = { 0, 0, -1, +1 };
const int dx[] = { -1, +1, 0, 0 };
 
int main()
{
    scanf("%d", &n);
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            scanf("%d", &map[y][x]);
            if (map[y][x] == 9) {
                shark.y = y, shark.x = x, shark.time = 0;
                shark_size = 2, shark_eat = 0;
                map[y][x] = 0;
            }
        }
    }
 
    bool is_update = true;
    while (is_update) {
        is_update = false;
 
        bool visited[20][20] = { false, };
        queue<shark> q;
        visited[shark.y][shark.x] = true;
        q.push(shark);
 
        SHARK candi;
        candi.y = 20, candi.time = -1;
        while (!q.empty()) {
            SHARK cur = q.front();  q.pop();
 
            if (candi.time != -1 && candi.time < cur.time) {//적절한 먹이를 찾았고 && 그림자 분신인 cur 의 시간이 적절한 먹이의 위치에 있는 proper의 시간보다 클떄
                break;//큐를 더이상 진행하지 않는다
            }
 
            if (map[cur.y][cur.x] < shark_size && map[cur.y][cur.x] != 0) {// 먹이에 대한 경우
                is_update = true;
                if (candi.y > cur.y || (candi.y == cur.y && candi.x > cur.x)) {
                    candi = cur;
                }
            }
 
            for (int dir = 0; dir < 4; ++dir) {
                SHARK next;
                next.y = cur.y + dy[dir];
                next.x = cur.x + dx[dir];
                next.time = cur.time + 1;
 
                if (next.y < 0 || next.y >= n || next.x < 0 || next.x >= n) {
                    continue;
                }
 
                if (visited[next.y][next.x] == false && shark_size >= map[next.y][next.x]) {
                    visited[next.y][next.x] = true;
                    q.push(next);
                }
            }
        }
 
        if (is_update) {
            shark = candi;
            ++shark_eat;
            if (shark_eat == shark_size) {
                ++shark_size;
                shark_eat = 0;
            }
            map[shark.y][shark.x] = 0;
        }
    }
 
    printf("%d\n", shark.time);
 
    return 0;
}


출처: https://na982.tistory.com/category/삼성 SW 역량 테스트 기출 풀이 [na982]
