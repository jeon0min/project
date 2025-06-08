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

void states(int SoupCount, int Relationship, int CP, int CF, char *CatName) {
  printf("\n\n==================== 현재 상태 ====================\n");
  printf("현재까지 만든 수프: %d개\n", SoupCount);
  printf("CP : %d 포인트\n", CP);
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
  printf("=================================================\n");
  printf("\n\n");
}

void interaction(char *CatName, int *Relationship) {
  int choice;
  int dice = RollDice();
  printf("어떤 상호작용을 하시겠습니까?  0. 아무것도 하지 않음 1. 긁어 주기\n");
  printf(">>");
  scanf("%d", &choice);
  if (choice == 0) {
    printf("아무것도 하지 않습니다.\n");
    printf("4/6의 확률로 친밀도가 떨어집니다.\n");
    printf("주사위를 굴립니다. 또르륵...\n");
    printf("%d이(가) 나왔습니다!\n", dice);
    if (dice <= 4) {
      *Relationship = (*Relationship > 0) ? *Relationship - 1 : 0;
      printf("친밀도가 떨어집니다.\n");
    } else {
      printf("다행이 친밀도가 떨어지지 않았습니다.\n");
    }
    printf("현재 친밀도 %d\n", *Relationship);
  } else if (choice == 1) {
    printf("%s의 턱을 긁어주었습니다.\n", CatName);
    printf("2/6의 확률로 친밀도가 높아집니다.\n");
    printf("주사위를 굴립니다. 또르륵...\n");
    printf("%d이(가) 나왔습니다!\n", dice);
    if (dice >= 5) {
      *Relationship = (*Relationship < 4) ? *Relationship + 1 : 4;
      printf("친밀도가 높아집니다.\n");
    } else {
      printf("친밀도는 그대로입니다.\n");
    }
    printf("현재 친밀도 : %d\n", *Relationship);
  }
  sleep(2);
  system(CLEAR_CONSOLE);
}

void CatRoom(int CatPosition, int *SoupCount, char *CatName) {
  for (int i = 0; i < ROOM_WIDTH + 2; i++) {
    printf("#");
  }
  printf("\n#");
  for (int i = 0; i < ROOM_WIDTH; i++) {
    if (i == HME_POS) {
      printf("H");
    } else if (i == BWL_PO) {
      printf("B");
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

void Catmove(int *CatPosition, int Relationship, int *CF, char *CatName) {
  printf("6-2: 주사위 눈이 %d이하면 그냥 기분이 나빠집니다.\n",
         6 - Relationship);
  printf("주사위를 굴립니다. 또르륵...\n");
  int dice = RollDice();
  sleep(1);
  printf("%d이(가) 나왔습니다!\n", dice);
  if (dice <= 6 - Relationship) {
    printf("%s의 기분이 나빠집니다: %d->", CatName, *CF);
    if (*CF > 0) {
      (*CF)--;
      printf("%d\n", *CF);
    } else {
      printf("더이상 기분이 나빠질수가 없습니다.\n");
    }
  }
  if (*CF == 0) {
    printf("기분이 매우 나쁜 %s은(는) 집으로 향합니다.\n", CatName);
  } else if (*CF == 1) {
    printf("%s은(는) 심심해서 스크래처 쪽으로 이동합니다.\n", CatName);
  } else if (*CF == 2) {
    printf("%s은(는) 기분좋게 식빵을 굽고 있습니다.\n", CatName);
  } else if (*CF == 3) {
    printf("%s은(는) 골골송을 부르며 수프를 만들러 갑니다.\n", CatName);
  }
}

void CatAction(int CatPosition, int *CF, int *CP, char *CatName) {
  if (CatPosition == HME_POS) {
    if (*CF < 3) {
      (*CF)++;
      printf("%s은(는) 집에서 쉬며 기분이 조금 나아졌습니다. 기분: %d\n",
             CatName, *CF);
    } else {
      printf("%s은(는) 집에서 쉬고 있습니다. 기분은 이미 최고입니다.\n",
             CatName);
    }
  } else if (CatPosition == ROOM_WIDTH / 2) {
    printf("%s은(는) 스크래처를 긁으며 기분 전환을 시도합니다.\n", CatName);
    if (*CF < 3) (*CF)++;
  } else if (CatPosition == ROOM_WIDTH / 2 + 1) {
    printf("%s은(는) 캣타워에서 놉니다. CP가 +1 증가합니다.\n", CatName);
    (*CP)++;
  }
}

int main(void) {
  char CatName[10];
  int SoupCount = 0, Relationship = 2, CatPosition = 0, CP = 0, CF = 3;
  srand((unsigned int)time(NULL));
  intro(CatName);
  while (1) {
    states(SoupCount, Relationship, CP, CF, CatName);
    Catmove(&CatPosition, Relationship, &CF, CatName);
    printf("\n");
    CatRoom(CatPosition, &SoupCount, CatName);
    printf("\n");
    CatAction(CatPosition, &CF, &CP, CatName);
    interaction(CatName, &Relationship);
    sleep(1);
    system(CLEAR_CONSOLE);
  }
  return 0;
}
