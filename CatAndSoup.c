#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#define sleep(seconds) Sleep((seconds) * 1000)
#define CLEAR_CONSOLE "cls"
#elif defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#define CLEAR_CONSOLE "clear"
#else
#error "Unsupported OS"
#endif

#define ROOM_WIDTH 10
#define HME_POS 0
#define BWL_PO (ROOM_WIDTH - 1)

int RollDice() { return rand() % 6 + 1; }

int MouseToy = 0;
int RazerPointer = 0;
int CF = 3;
int CatTower = 0;
int Scratcher = 0;

void intro(char* CatName) {
    printf("**** �߿��̿� ����****\n");
    printf("      /\\_/\\\n");
    printf(" /\\  / o o \\\n");
    printf("//\\\\ \\~(*)~/\n");
    printf("`  \\/   ^ /\n");
    printf("   | \\|| ||\n");
    printf("   \\ '|| ||\n");
    printf("    \\)()-())\n\n");
    printf("\n\n");
    printf("�߿����� �̸��� �����ּ���:");
    scanf_s("%s", CatName, 10);
    printf("�߿����� �̸��� %s�Դϴ�.\n", CatName);
    sleep(2);
    system(CLEAR_CONSOLE);
}

void states(int SoupCount, int Relationship, int CP, int CF, char* CatName,
    int lastProducedCP) {
    printf("\n\n==================== ���� ���� ====================\n");
    printf("������� ���� ����: %d��\n", SoupCount);
    printf("���� CP : %d ����Ʈ\n", CP);
    printf("%s�� ���(0~3): %d\n", CatName, CF);
    switch (CF) {
    case 0:
        printf("  ����� �ſ� ���޴ϴ�.\n");
        break;
    case 1:
        printf("  �ɽ����մϴ�.\n");
        break;
    case 2:
        printf("  �Ļ��� �����ϴ�.\n");
        break;
    case 3:
        printf("  ������ �θ��ϴ�.\n");
        break;
    }
    printf("������� ����(0~4): %d\n", Relationship);
    switch (Relationship) {
    case 0:
        printf("  �翡 ���� ������ �Ⱦ��մϴ�.\n");
        break;
    case 1:
        printf("  ���� ���Ǳ� ����Դϴ�.\n");
        break;
    case 2:
        printf("  �׷����� �� ���� �����Դϴ�.\n");
        break;
    case 3:
        printf("  �Ǹ��� ����� ���� �ް� �ֽ��ϴ�.\n");
        break;
    case 4:
        printf("  ���� �������Դϴ�.\n");
        break;
    }
    printf("%s�� ��а� ģ�е��� ���� CP�� %d����Ʈ ���� �Ǿ����ϴ�.\n",
        CatName, lastProducedCP);
    printf("=================================================\n");
    printf("\n\n");
}

void CatAction(int CatPosition, int* CF, int* CP, char* CatName,
    int CatTowerPos, int ScratcherPos, int* prevCatPosition) {
    if (CatPosition == HME_POS) {
        if (*prevCatPosition != HME_POS) {
        }
        else {
            if (*CF < 3) {
                int before = *CF;
                (*CF)++;
                printf("%s��(��) ������ ���� ����� ���� ���������ϴ�. ���: %d->%d\n",
                    CatName, before, *CF);
            }
            else {
                printf("%s��(��) ������ ���� �ֽ��ϴ�. ����� �̹� �ְ��Դϴ�.\n",
                    CatName);
            }
        }
    }
    else if (CatPosition == ScratcherPos) {
        int before = *CF;
        if (*CF < 3) (*CF)++;
        printf("%s��(��) ��ũ��ó�� �ܰ� ��ҽ��ϴ�.\n", CatName);
        printf("����� ���� ���������ϴ�: %d->%d\n", before, *CF);
    }
    else if (CatPosition == CatTowerPos) {
        int before = *CF;
        int after = *CF + 2;
        if (after > 3) after = 3;
        printf("%s��(��) ĹŸ���� �پ�ٴմϴ�.\n", CatName);
        printf("����� ���� ���������ϴ�: %d->%d\n", before, after);
        *CF = after;
    }
    *prevCatPosition = CatPosition;
}

void interaction(char* CatName, int* Relationship) {
    int choice;
    int dice = RollDice();
    int menu_idx = 2;
    int menu_map[4];
    printf("� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?\n");
    printf("  0. �ƹ��͵� ���� ����\n");
    menu_map[0] = 0;
    printf("  1. �ܾ� �ֱ�\n");
    menu_map[1] = 1;
    if (MouseToy == 1 && RazerPointer == 1) {
        printf("  2. �峭�� ��� ����ֱ�\n");
        menu_map[2] = 2;
        printf("  3. �������� �����ͷ� ��� �ֱ�\n");
        menu_map[3] = 3;
        menu_idx = 4;
    }
    else if (MouseToy == 1) {
        printf("  2. �峭�� ��� ����ֱ�\n");
        menu_map[2] = 2;
        menu_idx = 3;
    }
    else if (RazerPointer == 1) {
        printf("  2. �������� �����ͷ� ��� �ֱ�\n");
        menu_map[2] = 3;
        menu_idx = 3;
    }
    printf(">>");
    scanf_s("%d", &choice);
    if (choice < 0 || choice >= menu_idx) {
        printf("�߸��� �Է��Դϴ�.\n");
        sleep(2);
        system(CLEAR_CONSOLE);
        return;
    }
    int action = menu_map[choice];
    if (action == 0) {
        int prevCF = CF;
        if (CF > 0) CF--;
        printf("%s�� ����� ���������ϴ�: %d->%d\n", CatName, prevCF, CF);
        dice = RollDice();
        if (dice <= 5) {
            int prevRel = *Relationship;
            if (*Relationship > 0) (*Relationship)--;
            printf("������� ���谡 �������ϴ�.\n");
        }
    }
    else if (action == 1) {
        printf("%s�� ����� �״���Դϴ�: %d\n", CatName, CF);
        dice = RollDice();
        if (dice >= 5) {
            if (*Relationship < 4) (*Relationship)++;
            printf("������� ���谡 �������ϴ�.\n");
        }
    }
    else if (action == 2) {
        int prevCF = CF;
        if (CF < 3) CF++;
        printf(
            "�峭�� ��� %s�� ����־����ϴ�. %s�� ����� ���� ���������ϴ�: "
            "%d->%d\n",
            CatName, CatName, prevCF, CF);
        dice = RollDice();
        if (dice >= 4) {
            if (*Relationship < 4) (*Relationship)++;
            printf("������� ���谡 �������ϴ�.\n");
        }
    }
    else if (action == 3) {
        int prevCF = CF;
        CF += 2;
        if (CF > 3) CF = 3;
        printf(
            "������ �����ͷ� %s�� �ų��� ��� �־����ϴ�. %s�� ����� �� "
            "���������ϴ�: %d->%d\n",
            CatName, CatName, prevCF, CF);
        dice = RollDice();
        if (dice >= 2) {
            if (*Relationship < 4) (*Relationship)++;
            printf("������� ���谡 �������ϴ�.\n");
        }
    }
    sleep(2);
    system(CLEAR_CONSOLE);
}

void CatRoom(int CatPosition, int* SoupCount, char* CatName, int CatTowerPos,
    int ScratcherPos) {
    for (int i = 0; i < ROOM_WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n#");
    for (int i = 0; i < ROOM_WIDTH; i++) {
        if (i == HME_POS) {
            printf("H");
        }
        else if (i == BWL_PO) {
            printf("B");
        }
        else if (CatTower && i == CatTowerPos) {
            printf("T");
        }
        else if (Scratcher && i == ScratcherPos) {
            printf("S");
        }
        else {
            printf(" ");
        }
    }
    printf("#\n");

    printf("#");
    for (int i = 0; i < ROOM_WIDTH; i++) {
        if (i < CatPosition) {
            printf(".");
        }
        else if (i == CatPosition) {
            printf("C");
        }
        else {
            printf(" ");
        }
    }
    printf("#\n");

    for (int i = 0; i < ROOM_WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    printf("\n");
    if (CatPosition == HME_POS) {
        printf("%s��(��) �ڽ��� ������ ������� �����ϴ�.\n", CatName);
    }

    if (CatPosition == BWL_PO) {
        const char* selectedSoup;
        int soupType = rand() % 3;
        if (soupType == 0) {
            selectedSoup = "���� ����";
        }
        else if (soupType == 1) {
            selectedSoup = "����� ����";
        }
        else {
            selectedSoup = "����ݸ� ����";
        }
        printf("�߿��̰� %s�� ��������ϴ�!\n", selectedSoup);
        (*SoupCount)++;
    }
}

void Catmove(int* CatPosition, int Relationship, int* CF, char* CatName,
    int Scratcher, int CatTower) {
    printf("6-2: �ֻ��� ���� %d���ϸ� �׳� ����� �������ϴ�.\n",
        6 - Relationship);
    printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
    int dice = RollDice();
    sleep(1);
    printf("%d��(��) ���Խ��ϴ�!\n", dice);
    if (dice >= 6 - Relationship && *CatPosition < ROOM_WIDTH - 1) {
        (*CatPosition)++;
        printf("���� ������ �����Դϴ�.\n");
    }
    else if (*CatPosition > 0) {
        (*CatPosition)--;
        printf("�� ������ �����Դϴ�.\n");
    }
    if (dice <= 6 - Relationship) {
        printf("%s�� ����� �������ϴ�: %d->", CatName, *CF);
        if (*CF > 0) {
            (*CF)--;
            printf("%d\n", *CF);
        }
        else {
            printf("ȭ�� ���� ���ִ� �����Դϴ�.\n");
        }
    }
    if (*CF == 0) {
        printf("����� �ſ� ���� %s��(��) ������ ���մϴ�.\n", CatName);
    }
    else if (*CF == 1) {
        printf("%s��(��) �ɽ��ؼ� ��ũ��ó ������ �̵��մϴ�.\n", CatName);
        if (CatTower == 0 && Scratcher == 0) {
            printf("�� �Ÿ��� ��� ����� �ſ� �������ϴ�.");
            (*CF)--;
        }
    }
    else if (*CF == 2) {
        printf("%s��(��) ������� �Ļ��� ���� �ֽ��ϴ�.\n", CatName);
    }
    else if (*CF == 3) {
        printf("%s��(��) ������ �θ��� ������ ���鷯 ���ϴ�.\n", CatName);
    }
}

void shop(int* CP, int* MouseToy, int* RazerPointer, int* Scratcher,
    int* CatTower, int* ScratcherPos, int* CatTowerPos) {
    int buy = -1;
    while (1) {
        printf("�������� ������ �� �� �ֽ��ϴ�.\n");
        printf("� ������ �����ұ��?\n");
        printf("0. �ƹ��͵� ���� �ʴ´�.\n");
        printf("1. �峭�� �� : 1CP%s\n", *MouseToy ? " (ǰ��)" : "");
        printf("2. ������ ������ : 2CP%s\n", *RazerPointer ? " (ǰ��)" : "");
        printf("3. ��ũ��ó: 4 CP%s\n", *Scratcher ? " (ǰ��)" : "");
        printf("4. Ĺ Ÿ��: 6CP%s\n", *CatTower ? " (ǰ��)" : "");
        printf(">> ");
        scanf_s("%d", &buy);

        if (buy < 0 || buy > 4) {
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
            continue;
        }
        if (buy == 0) break;

        if (buy == 1) {
            if (*MouseToy) {
                printf("�峭�� �㸦 �̹̱����߽��ϴ�.\n");
            }
            else if (*CP < 1) {
                printf("CP�� �����մϴ�.\n");
            }
            else {
                (*CP) -= 1;
                *MouseToy = 1;
                printf("�峭�� �㸦 �����߽��ϴ�.\n");
                printf("����CP %d ����Ʈ\n", *CP);
            }
            break;
        }
        else if (buy == 2) {
            if (*RazerPointer) {
                printf("������ �����͸� �̹̱����߽��ϴ�.\n");
            }
            else if (*CP < 2) {
                printf("CP�� �����մϴ�.\n");
            }
            else {
                (*CP) -= 2;
                *RazerPointer = 1;
                printf("������ �����͸� �����߽��ϴ�.\n");
                printf("����CP %d ����Ʈ\n", *CP);
            }
            break;
        }
        else if (buy == 3) {
            if (*Scratcher) {
                printf("��ũ��ó�� �̹̱����߽��ϴ�.\n");
            }
            else if (*CP < 4) {
                printf("CP�� �����մϴ�.\n");
            }
            else {
                (*CP) -= 4;
                *Scratcher = 1;
                int pos;
                do {
                    pos = rand() % ROOM_WIDTH;
                } while (pos == HME_POS || pos == BWL_PO ||
                    (*CatTower && pos == *CatTowerPos));
                *ScratcherPos = pos;
                printf("��ũ��ó�� �����߽��ϴ�.\n");
                printf("����CP %d ����Ʈ\n", *CP);
            }
            break;
        }
        else if (buy == 4) {
            if (*CatTower) {
                printf("Ĺ Ÿ���� �̹̱����߽��ϴ�.\n");
            }
            else if (*CP < 6) {
                printf("CP�� �����մϴ�.\n");
            }
            else {
                (*CP) -= 6;
                *CatTower = 1;
                int pos;
                do {
                    pos = rand() % ROOM_WIDTH;
                } while (pos == HME_POS || pos == BWL_PO ||
                    (*Scratcher && pos == *ScratcherPos));
                *CatTowerPos = pos;
                printf("Ĺ Ÿ���� �����߽��ϴ�.\n");
                printf("����CP %d ����Ʈ\n", *CP);
            }
            break;
        }
    }
}

void sudden_quest(char* CatName, int* CP) {
    int answer, tries = 0;
    int correct = rand() % 10 + 1;
    printf("\n[���� ����Ʈ] %s�� ���ڱ� ���� ������ ã������ �մϴ�!\n", CatName);
    printf("1~10 ���̿� ������ ������ �ֽ��ϴ�. ���� ������ �Է��ϼ���!\n");
    while (1) {
        printf("��� ���������? >> ");
        scanf_s("%d", &answer);
        tries++;
        if (answer == correct) {
            printf("����! %d���� ������ �־����ϴ�! (%d�� ���� ����)\n", correct,
                tries);
            printf("�������� CP 2����Ʈ�� ������ϴ�!\n");
            *CP += 2;
            break;
        }
        else if (answer < correct) {
            printf("�� ���� ��ȣ�� �ֽ��ϴ�!\n");
        }
        else {
            printf("�� ���� ��ȣ�� �ֽ��ϴ�!\n");
        }
    }
    sleep(2);
    system(CLEAR_CONSOLE);
}

int main(void) {
    char CatName[10];
    int SoupCount = 0, Relationship = 2, CatPosition = 0, CP = 0;
    int CatTowerPos, ScratcherPos;
    int prevCatPosition = HME_POS;
    int turn = 0;
    srand((unsigned int)time(NULL));
    do {
        CatTowerPos = rand() % ROOM_WIDTH;
    } while (CatTowerPos == HME_POS || CatTowerPos == BWL_PO);
    do {
        ScratcherPos = rand() % ROOM_WIDTH;
    } while (ScratcherPos == HME_POS || ScratcherPos == BWL_PO ||
        ScratcherPos == CatTowerPos);
    intro(CatName);
    while (1) {
        turn++;
        int producedCP = (CF > 1 ? CF - 1 : 0) + Relationship;
        CP += producedCP;
        states(SoupCount, Relationship, CP, CF, CatName, producedCP);
        if (turn == 3) sudden_quest(CatName, &CP);
        shop(&CP, &MouseToy, &RazerPointer, &Scratcher, &CatTower, &ScratcherPos,
            &CatTowerPos);
        Catmove(&CatPosition, Relationship, &CF, CatName, Scratcher, CatTower);
        printf("\n");
        CatRoom(CatPosition, &SoupCount, CatName, CatTowerPos, ScratcherPos);
        printf("\n");
        CatAction(CatPosition, &CF, &CP, CatName, CatTowerPos, ScratcherPos,
            &prevCatPosition);
        interaction(CatName, &Relationship);
        sleep(1);
        system(CLEAR_CONSOLE);
    }
    return 0;
}
// ��