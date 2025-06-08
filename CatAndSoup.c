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

void intro(char *CatName) {
  printf("**** 야옹이와 수프****\n");
  printf("      /\\_/\\\n");
  printf(" /\\  / o o \\\n");
  printf("//\\\\ \\~(*)~/\n");
  printf("`  \\/   ^ /\n");
  printf("   | \\|| ||\n");
  printf("   \\ '|| ||\n");
  printf("    \\)()-())\n\n");
  printf("\n\n");
  printf("야옹이의 이름을 지어주세요:");
  scanf("%s", CatName);
  printf("야옹이의 이름은 %s입니다.\n", CatName);
  sleep(2);
  system(CLEAR_CONSOLE);
}

void states(int SoupCount, int Relationship, int CP, int CF, char *CatName,
            int lastProducedCP) {
  printf("\n\n==================== 현재 상태 ====================\n");
  printf("현재까지 만든 수프: %d개\n", SoupCount);
  printf("보유 CP : %d 포인트\n", CP);
  printf("%s이 기분(0~3): %d\n", CatName, CF);
  switch (CF) {
    case 0:
      printf("  기분이 매우 나쁩니다.\n");
      break;
    case 1:
      printf("  심심해합니다.\n");
      break;
    case 2:
      printf("  식빵을 굽습니다.\n");
      break;
    case 3:
      printf("  골골송을 부릅니다.\n");
      break;
  }
  printf("집사와의 관계(0~4): %d\n", Relationship);
  switch (Relationship) {
    case 0:
      printf("  곁에 오는 것조차 싫어합니다.\n");
      break;
    case 1:
      printf("  간식 자판기 취급입니다.\n");
      break;
    case 2:
      printf("  그럭저럭 쓸 만한 집사입니다.\n");
      break;
    case 3:
      printf("  훌륭한 집사로 인정 받고 있습니다.\n");
      break;
    case 4:
      printf("  집사 껌딱지입니다.\n");
      break;
  }
  printf("%s의 기분과 친밀도에 따라서 CP가 %d포인트 생산 되었습니다.\n",
         CatName, lastProducedCP);
  printf("=================================================\n");
  printf("\n\n");
}

void CatAction(int CatPosition, int *CF, int *CP, char *CatName,
               int CatTowerPos, int ScratcherPos, int *prevCatPosition) {
  if (CatPosition == HME_POS) {
    if (*prevCatPosition != HME_POS) {
    } else {
      if (*CF < 3) {
        int before = *CF;
        (*CF)++;
        printf("%s은(는) 집에서 쉬며 기분이 조금 나아졌습니다. 기분: %d->%d\n",
               CatName, before, *CF);
      } else {
        printf("%s은(는) 집에서 쉬고 있습니다. 기분은 이미 최고입니다.\n",
               CatName);
      }
    }
  } else if (CatPosition == ScratcherPos) {
    int before = *CF;
    if (*CF < 3) (*CF)++;
    printf("%s은(는) 스크래처를 긁고 놀았습니다.\n", CatName);
    printf("기분이 조금 좋아졌습니다: %d->%d\n", before, *CF);
  } else if (CatPosition == CatTowerPos) {
    int before = *CF;
    int after = *CF + 2;
    if (after > 3) after = 3;
    printf("%s은(는) 캣타워를 뛰어다닙니다.\n", CatName);
    printf("기분이 제법 좋아졌습니다: %d->%d\n", before, after);
    *CF = after;
  }
  *prevCatPosition = CatPosition;
}

void interaction(char *CatName, int *Relationship) {
  int choice;
  int dice = RollDice();
  int menu_idx = 2;
  int menu_map[4];
  printf("어떤 상호작용을 하시겠습니까?\n");
  printf("  0. 아무것도 하지 않음\n");
  menu_map[0] = 0;
  printf("  1. 긁어 주기\n");
  menu_map[1] = 1;
  if (MouseToy == 1 && RazerPointer == 1) {
    printf("  2. 장난감 쥐로 놀아주기\n");
    menu_map[2] = 2;
    printf("  3. 레이저로 포인터로 놀아 주기\n");
    menu_map[3] = 3;
    menu_idx = 4;
  } else if (MouseToy == 1) {
    printf("  2. 장난감 쥐로 놀아주기\n");
    menu_map[2] = 2;
    menu_idx = 3;
  } else if (RazerPointer == 1) {
    printf("  2. 레이저로 포인터로 놀아 주기\n");
    menu_map[2] = 3;
    menu_idx = 3;
  }
  printf(">>");
  scanf("%d", &choice);
  if (choice < 0 || choice >= menu_idx) {
    printf("잘못된 입력입니다.\n");
    sleep(2);
    system(CLEAR_CONSOLE);
    return;
  }
  int action = menu_map[choice];
  if (action == 0) {
    int prevCF = CF;
    if (CF > 0) CF--;
    printf("%s의 기분이 나빠졌습니다: %d->%d\n", CatName, prevCF, CF);
    dice = RollDice();
    if (dice <= 5) {
      int prevRel = *Relationship;
      if (*Relationship > 0) (*Relationship)--;
      printf("집사와의 관계가 나빠집니다.\n");
    }
  } else if (action == 1) {
    printf("%s의 기분은 그대로입니다: %d\n", CatName, CF);
    dice = RollDice();
    if (dice >= 5) {
      if (*Relationship < 4) (*Relationship)++;
      printf("집사와의 관계가 좋아집니다.\n");
    }
  } else if (action == 2) {
    int prevCF = CF;
    if (CF < 3) CF++;
    printf(
        "장난감 쥐로 %s와 놀아주었습니다. %s의 기분이 조금 좋아졌습니다: "
        "%d->%d\n",
        CatName, CatName, prevCF, CF);
    dice = RollDice();
    if (dice >= 4) {
      if (*Relationship < 4) (*Relationship)++;
      printf("집사와의 관계가 좋아집니다.\n");
    }
  } else if (action == 3) {
    int prevCF = CF;
    CF += 2;
    if (CF > 3) CF = 3;
    printf(
        "레이저 포인터로 %s와 신나게 놀아 주었습니다. %s의 기분이 꽤 "
        "좋아졌습니다: %d->%d\n",
        CatName, CatName, prevCF, CF);
    dice = RollDice();
    if (dice >= 2) {
      if (*Relationship < 4) (*Relationship)++;
      printf("집사와의 관계가 좋아집니다.\n");
    }
  }
  sleep(2);
  system(CLEAR_CONSOLE);
}

void CatRoom(int CatPosition, int *SoupCount, char *CatName, int CatTowerPos,
             int ScratcherPos) {
  // extern int CatTower;
  // extern int Scratcher;
  for (int i = 0; i < ROOM_WIDTH + 2; i++) {
    printf("#");
  }
  printf("\n#");
  for (int i = 0; i < ROOM_WIDTH; i++) {
    if (i == HME_POS) {
      printf("H");
    } else if (i == BWL_PO) {
      printf("B");
    } else if (CatTower && i == CatTowerPos) {
      printf("T");
    } else if (Scratcher && i == ScratcherPos) {
      printf("S");
    } else {
      printf(" ");
    }
  }
  printf("#\n");

  printf("#");
  for (int i = 0; i < ROOM_WIDTH; i++) {
    if (i < CatPosition) {
      printf(".");
    } else if (i == CatPosition) {
      printf("C");
    } else {
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
    printf("%s은(는) 자신의 집에서 편안함을 느낍니다.\n", CatName);
  }

  if (CatPosition == BWL_PO) {
    const char *selectedSoup;
    int soupType = rand() % 3;
    if (soupType == 0) {
      selectedSoup = "감자 수프";
    } else if (soupType == 1) {
      selectedSoup = "양송이 수프";
    } else {
      selectedSoup = "브로콜리 수프";
    }
    printf("야옹이가 %s를 만들었습니다!\n", selectedSoup);
    (*SoupCount)++;
  }
}

void Catmove(int *CatPosition, int Relationship, int *CF, char *CatName,
             int Scratcher, int CatTower) {
  printf("6-2: 주사위 눈이 %d이하면 그냥 기분이 나빠집니다.\n",
         6 - Relationship);
  printf("주사위를 굴립니다. 또르륵...\n");
  int dice = RollDice();
  sleep(1);
  printf("%d이(가) 나왔습니다!\n", dice);
  if (dice >= 6 - Relationship && *CatPosition < ROOM_WIDTH - 1) {
    (*CatPosition)++;
    printf("냄비 쪽으로 움직입니다.\n");
  } else if (*CatPosition > 0) {
    (*CatPosition)--;
    printf("집 쪽으로 움직입니다.\n");
  }
  if (dice <= 6 - Relationship) {
    printf("%s의 기분이 나빠집니다: %d->", CatName, *CF);
    if (*CF > 0) {
      (*CF)--;
      printf("%d\n", *CF);
    } else {
      printf("화가 많이 나있는 상태입니다.\n");
    }
  }
  if (*CF == 0) {
    printf("기분이 매우 나쁜 %s은(는) 집으로 향합니다.\n", CatName);
  } else if (*CF == 1) {
    printf("%s은(는) 심심해서 스크래처 쪽으로 이동합니다.\n", CatName);
    if (CatTower == 0 && Scratcher == 0) {
      printf("놀 거리가 없어서 기분이 매우 나빠집니다.");
      (*CF)--;
    }
  } else if (*CF == 2) {
    printf("%s은(는) 기분좋게 식빵을 굽고 있습니다.\n", CatName);
  } else if (*CF == 3) {
    printf("%s은(는) 골골송을 부르며 수프를 만들러 갑니다.\n", CatName);
  }
}

void shop(int *CP, int *MouseToy, int *RazerPointer, int *Scratcher,
          int *CatTower, int *ScratcherPos, int *CatTowerPos) {
  int buy = -1;
  int bought = 0;
  while (1) {
    printf("상점에서 물건을 살 수 있습니다.\n");
    printf("어떤 물건을 구매할까요?\n");
    printf("0. 아무것도 사지 않는다.\n");
    printf("1. 장난감 쥐 : 1CP%s\n", *MouseToy ? " (품절)" : "");
    printf("2. 레이저 포인터 : 2CP%s\n", *RazerPointer ? " (품절)" : "");
    printf("3. 스크래처: 4 CP%s\n", *Scratcher ? " (품절)" : "");
    printf("4. 캣 타워: 6CP%s\n", *CatTower ? " (품절)" : "");
    printf(">> ");
    scanf("%d", &buy);

    if (buy < 0 || buy > 4) {
      printf("잘못된 입력입니다. 다시 입력해주세요.\n");
      continue;
    }
    if (buy == 0) break;

    if (buy == 1) {
      if (*MouseToy) {
        printf("장난감 쥐를 이미구매했습니다.\n");
      } else if (*CP < 1) {
        printf("CP가 부족합니다.\n");
      } else {
        (*CP) -= 1;
        *MouseToy = 1;
        printf("장난감 쥐를 구매했습니다.\n");
        printf("보유CP %d 포인트\n", *CP);
        break;
      }
    } else if (buy == 2) {
      if (*RazerPointer) {
        printf("레이저 포인터를 이미구매했습니다.\n");
      } else if (*CP < 2) {
        printf("CP가 부족합니다.\n");
      } else {
        (*CP) -= 2;
        *RazerPointer = 1;
        printf("레이저 포인터를 구매했습니다.\n");
        printf("보유CP %d 포인트\n", *CP);
        break;
      }
    } else if (buy == 3) {
      if (*Scratcher) {
        printf("스크래처를 이미구매했습니다.\n");
      } else if (*CP < 4) {
        printf("CP가 부족합니다.\n");
      } else {
        (*CP) -= 4;
        *Scratcher = 1;
        int pos;
        do {
          pos = rand() % ROOM_WIDTH;
        } while (pos == HME_POS || pos == BWL_PO ||
                 (CatTower && pos == *CatTowerPos));
        *ScratcherPos = pos;
        printf("스크래처를 구매했습니다.\n");
        printf("보유CP %d 포인트\n", *CP);
        break;
      }
    } else if (buy == 4) {
      if (*CatTower) {
        printf("캣 타워를 이미구매했습니다.\n");
      } else if (*CP < 6) {
        printf("CP가 부족합니다.\n");
      } else {
        (*CP) -= 6;
        *CatTower = 1;
        int pos;
        do {
          pos = rand() % ROOM_WIDTH;
        } while (pos == HME_POS || pos == BWL_PO ||
                 (Scratcher && pos == *ScratcherPos));
        *CatTowerPos = pos;
        printf("캣 타워를 구매했습니다.\n");
        printf("보유CP %d 포인트\n", *CP);
        break;
      }
    }
  }
}

int main(void) {
  char CatName[10];
  int SoupCount = 0, Relationship = 2, CatPosition = 0, CP = 0;
  int CatTowerPos, ScratcherPos;
  int prevCatPosition = HME_POS;
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
    int producedCP = (CF > 1 ? CF - 1 : 0) + Relationship;
    CP += producedCP;
    states(SoupCount, Relationship, CP, CF, CatName, producedCP);
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
