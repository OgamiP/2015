//����4���ԁA�h���A�~�j�}�b�N�X�@�̏���CPU������
//�����c�Œu���Ȃ��ꍇ�̏�����ǉ�

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//�ՖʃT�C�Y
#define Size 12
//�Q�[���؃T�C�Y
#define Game_Tree_Size 10000
//�~�j�}�b�N�X�@�̐[��
#define Depth 3
//�萔�̏��
#define Number_of_Moves 72

/*****�֐��v���g�^�C�v�錾*****/

//�Ֆʏ�񏉊���
void Initialization_Board();
//�Q�[���X�^�[�g
int Game_Start();

//�s����̔Ֆʂ�\��
void Show_Board();

//�e�v���C���[�s��which:���F���s�����邩
int Player_Turn(int Board[Size][Size],int which);

//�R���s���[�^���̎�����肷��(�����v���C���[�̔���
int CPU_Turn(int which);

//���s����which:�ǂ��瑤�̔�������邩
int Game_Judge(int which);

//������������
int Game_Judge_Draw();

//�Q�[���؍\�z�֐�
void Create_Game_Tree();

//�]���l�Z�o�֐�
int Evaluation_Value_Calc();

//�e�m�[�h����q�m�[�h���萔�̐������W�J����֐�
int Create_Child_Node(int Parent_Node_Number);

//�~�j�}�b�N�X�@(����������ǂސ[���ɂ��邩�H)
int Min_Max();

//�]���֐�����:�]���l�����߂�m�[�h�ԍ�
int Evaluation_Fanction(int which,int Node_Number,int Board_Label_Wide,int Board_Label_Height);

//�e�m�[�h�̔Ֆʍ\�z �u���ꏊ�Ɖ��F��u����
void Create_Board(int Position,int which,int node_number);

//�m�[�h�Ֆʏ��̔ՖʃR�s�[
int Board_Copy();

//�Q�[���ؗאڍs��(���ݑÓ��ȃT�C�Y�s��:���������I�m�ۂ͍s��Ȃ����j)
int Game_Tree[Game_Tree_Size][Game_Tree_Size];

//�]���l�i�[�z��i�z��v�f�w��ł��̃m�[�h�̕]���l���i�[�j
int Evaluation_Value[Game_Tree_Size];

//�ЂƂu�����Ƃ��A���A�������͑��肪3������Ă���Ƃ���ɒu���A�s��(����:�u���F ��:1 ��:0)
int Find_Vic_Def_Point(int which);



/******************************/

/*****�O���[�o���ϐ�*****/
//���݂̔Ֆ�
int Current_Board[Size][Size];

//�ςݏd�ˋL���|�C���^�[�z��
int *Board_Pointer;

//�ςݏd�ˋL���|�C���^�[����ϐ�
int BP0=Size-1,BP1=Size-1,BP2=Size-1,BP3=Size-1,BP4=Size-1, BP5=Size-1,BP6=Size-1,
	BP7=Size-1,BP8=Size-1,BP9=Size-1,BP10=Size-1,BP11=Size-1;

//���݂ǂ��炪�s�����Ă��邩
int Game_Side = 0;//0:��1:��

//�萔�Ǘ��ϐ�
int Number_of_Move_Count = 0;

//�Q�[���I���t���O
int Game_End_Flag = 10;//�����l-1,0,1�ȊO�����Ȃ�

//���ݍ\�z���̖؂̐e�m�[�h�̃m�[�h�̐[���ʒu
int Current_Depth = 0;

//�Q�[���؍\�z:���̐[���̓W�J�J�n�m�[�h�Z�o�t���O:0:�Z�o1:�Z�o���Ȃ�
int Next_Node_Flag = 0;

//���ɓW�J����e�m�[�h
int Next_Parent_Node;

//�]���l�i�[�z��i�z��v�f�w��ł��̃m�[�h�̕]���l���i�[�j
int Evaluation_Value[Game_Tree_Size];

//�Q�[���؂̃m�[�h�ԍ��ݒ�Ɏg�p
int Node_Number = 0;

//CPU�̎肪���肵�����ǂ����̃t���O(����:1 ������:0)
int CPU_Decision = 0;

//�m�[�h�ƔՖʊہX���\���̂ŊǗ�node�����m�� Game_Tree_Node[�m�[�h�ԍ�]�̂悤�ȃA�N�Z�X���@
struct Game_Tree_Node
{
	//���̃m�[�h��Parent�m�[�h
	int This_Node_Parent;

	//���̃m�[�h�̐[�����
	int This_Node_Depth;

	//�J�ڐ�m�[�h�z��
	int State_Node[12];
	//�J�ڐ�m�[�h�z��̐���ϐ�(�J�ڂ���Ƃ��̎�ɂ����p)
	int State_Number;
	//�J�ڎ�
	int State_Hand;

	//�e�̕]���l�����߂�ہAmax��min�ǂ�������߂鑤�ɓ����Ă��邩
	//max:1 min:0
	int Max_or_Min;

	//(�K�v���͌����̕K�v�A��)�Ֆʍ\�z�̍۔����ǂ�����u���̂�
	//white:0 black:1
	int which;

	//���̃m�[�h�̔Ֆʏ��
	int This_Node_Board_Info[Size][Size];

	//���̃m�[�h�̕]���l
	int This_Node_Evaluation_Value;

};

//���I�Ɋm�ۂ����\����(���ۂɑ���Ɏg������)
struct Game_Tree_Node *Use_Game_Tree;




/************************/

//main
//���� human �l�ԑ��X�^�[�g�@cpu���X�^�[�g
int main(int argc, char *argv[])
{

		//���߂Ƀm�[�h�\���̂��m�[�h�������m�ۂ���
		//���݂͊m�ۂ�����͌Œ肵�A���I�Ɋm�ۂ���
		Use_Game_Tree = (struct Game_Tree_Node*)malloc(sizeof(struct Game_Tree_Node) * Game_Tree_Size);
		if(Use_Game_Tree == NULL)
		{
			//�����������Ȃ��ꍇ���̎|��\�����A�����I��������
			printf("memory missed\n");
			exit(0);	
		}
		

	//���A���ݒ�
	if(strcmp(argv[1],"human") == 0)
	{
		Game_Side = 0;


	}else if(strcmp(argv[1],"cpu") == 0)
	{

		Game_Side = 1;

	}

	//�Ֆʏ�񏉊���
	Initialization_Board();

	//�Q�[���J�n
	Game_Start();

	if(Game_End_Flag == -1)
		printf("Draw\n");
	

	if(Game_End_Flag == 0)
		printf("Player1 Win\n");
	
	if(Game_End_Flag == 1)
		printf("Player2 Win\n");

	return 0;

}

/*****�Ֆʏ�����*****

�z��v�f...
-1  �� ��
1	��	X(��)
0	��  0(��)

********************/
void Initialization_Board()
{
	//���[�v����ϐ�
	int i = 0,j = 0;

	//�{�[�h�|�C���^�[������
	Board_Pointer = (int*)malloc(sizeof(int) * Size);
	for(i=0;i<Size;i++)
		Board_Pointer[i] = 0;


	for(i=0;i<Size;i++)
	{
		/*
		Current_Board[i][j] = -1;
		printf("%d",Current_Board[i][j]);
		*/
		for(j=0;j<Size;j++)
		{
			Current_Board[i][j] = -1;
			if(Current_Board[i][j] == -1)
				printf(".");
			//printf("%d",Current_Board[i][j]);
		}
		printf("\n");

	}

	//�Քԍ��\��
	printf("0123456789AB\n");

}

//�Q�[���̎�
int Game_Start()
{
	//�Q�[���I���t���O
	/**********

	-1 = Draw
	0  = P1Win
	1  = P21Win

	**********/

	//�e�v���C���[�s��
	while(1)
	{
	//�v���C���[�̍s���͎������[�v���s������㏈������
		Player_Turn(Current_Board,Game_Side);
		if(Game_End_Flag != 10)
		{
			if(Game_End_Flag == -1)
				return Game_End_Flag;
			if(Game_End_Flag == 0)
				return Game_End_Flag;
			if(Game_End_Flag == 1)
				return Game_End_Flag;
		}

		//�v���C���[��㏈��
		if(Game_Side == 0)
		{
			Game_Side = 1;

		}else if(Game_Side == 1){

			Game_Side = 0;
		}

	}

}

//�e�v���C���[�s��
int Player_Turn(int Board[Size][Size],int which)
{
	char Input_Board_Number_C[256] , *error;//���͂͏��߂����Ɋi�[��ɔ���e�͕ϊ��s���̕ԊҐ�
	int Input_Board_Number;
	int Domination_Board_Pointer;//���삷��{�[�h�|�C���^�L��
	int Player_Number = 1;//�\������v���C���[�ԍ�
	//P1���ǂ��ɂ�����
	//���͂��m�F���閳���ł���΍ē���
	while(1)
	{
		if(which == 0)
		{
			Player_Number = 1;

		}else if(which == 1){

			Player_Number = 2;
		}

		printf("Player%d:",Player_Number);
		if(which == 0)
		{
		//������Ƃ��Ċi�[
		scanf("%s",&Input_Board_Number_C);
		//�������16�i�ϊ�
		Input_Board_Number = strtol(Input_Board_Number_C,&error,16);
		}else if(which == 1)
		{
		
			//CPU�̎茈��t���O�����Z�b�g
			CPU_Decision = 0;
			Input_Board_Number = CPU_Turn(which);//which=1�̂Ƃ�cpu�̃^�[��(���u����cpu�ŌŒ�)
			printf("%d\n",Input_Board_Number);

		}
		


		

		//�����ł͒P���ɓ��͂�]������l�Ԃ�CPU�ł͕ʂŔ��肷��
		if(which == 0 && Input_Board_Number < 12  && strcmp("\0",error) == 0)
		{
			//�����ɍ����Δ�����
			break;
		}else if(which == 1 &&  Input_Board_Number < 12){
			break;
			
		}else{
			
			printf("error\n");

		}
	}

	//�X�^�b�N�|�C���^�[�Z���N�^�[
	switch(Input_Board_Number)
	{
		case 0:
			Domination_Board_Pointer = BP0;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP0 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
		case 1:
			Domination_Board_Pointer = BP1;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP1 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
		case 2:
			Domination_Board_Pointer = BP2;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP2 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
		case 3:
			Domination_Board_Pointer = BP3;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP3 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
		case 4:
			Domination_Board_Pointer = BP4;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP4 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
		case 5:
			Domination_Board_Pointer = BP5;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP5 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
		case 6:
			Domination_Board_Pointer = BP6;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP6 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
		case 7:
			Domination_Board_Pointer = BP7;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP7 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
		case 8:
			Domination_Board_Pointer = BP8;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP8 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
		case 9:
			Domination_Board_Pointer = BP9;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP9 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
		case 0x0A:
			Domination_Board_Pointer = BP10;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP10 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
		case 0x0B:
			Domination_Board_Pointer = BP11;
			Board[Domination_Board_Pointer][Input_Board_Number] = which;
			BP11 -= 1;//�ςݏd�˂����Ƃ��Ӗ�
			break;
	}
	
	//�Ֆʏ��\��
	Show_Board();
	//�萔�J�E���g
	Number_of_Move_Count += 1;
	//�萔�J�E���g����ň�����������
	if(Number_of_Move_Count == Number_of_Moves)
	{
		//������������Ƃ���
		Game_End_Flag = -1;
		return;
	}

	//���s����
	Game_Judge(which);
}

//�Ֆʕ\��
void Show_Board()
{
	//���[�v����ϐ�
	int i,j;
	
	//�����ɑΉ������Տ���\������
	for(i=0;i<Size;i++)
	{
		for(j=0;j<Size;j++)
		{
			if(Current_Board[i][j] == 0)
			{
				printf("0");
			}else if(Current_Board[i][j] == 1)
			{
				printf("X");
			}else{
				printf(".");
			}
		}
		printf("\n");
	}

	//�Քԍ��\��
	printf("0123456789AB\n");

}

//���s��������͂ǂ���̃^�[����judge���Ă��邩(0,1�ŋ�ʂ��Ă������)
int Game_Judge(int which)
{
	int i=0,j=0;//���[�v����ϐ�

	//���s���� �c���΂߂�4���������I��
	//�E������

			for(i=0;i<Size;i++)
			{
				for(j=0;j<Size-3;j++)
				if(Current_Board[i][j] == which &&Current_Board[i][j+1] == which &&Current_Board[i][j+2] == which &&Current_Board[i][j+3] == which)
				{
					Game_End_Flag = which;
					return;
				}
			}
			//��������
			for(i=0;i<Size;i++)
			{
				for(j=Size-1;j>4;j-=1)
				if(Current_Board[i][j] == which &&Current_Board[i][j-1] == which &&Current_Board[i][j-2] == which &&Current_Board[i][j-3] == which)
				{
					Game_End_Flag = which;
					return;
				}
			}
			//�����
			for(i=Size-1;i>Size-3;i-=1)
			{
				for(j=0;j<Size;j++)
				if(Current_Board[i][j] == which &&Current_Board[i-1][j] == which &&Current_Board[i-2][j] == which &&Current_Board[i-3][j] == which)
				{
					Game_End_Flag = which;
					return;
				}
			}
			//������
			for(i=0;i<Size-3;i++)
			{
				for(j=0;j<Size;j++)
				if(Current_Board[i][j] == which &&Current_Board[i+1][j] == which &&Current_Board[i+2][j] == which &&Current_Board[i+3][j] == which)
				{
					Game_End_Flag = which;
					return;
				}
			}
			//�E�����
			for(i=Size-1;i>Size-3;i-=1)
			{
				for(j=0;j<Size-3;j++)
				if(Current_Board[i][j] == which &&Current_Board[i-1][j+1] == which &&Current_Board[i-2][j+2] == which &&Current_Board[i-3][j+3] == which)
				{
					Game_End_Flag = which;
					return;
				}
			}
			//�������
			for(i=Size-1;i>Size-3;i-=1)
			{
				for(j=Size-1;j>3;j-=1)
				if(Current_Board[i][j] == which && Current_Board[i-1][j-1] == which && Current_Board[i-2][j-2] == which && Current_Board[i-3][j-3] == which)
				{
					Game_End_Flag = which;
					return;
				}
			}
			//�E������
			for(i=0;i<Size-3;i++)
			{
				for(j=0;j<Size-3;j++)
				if(Current_Board[i][j] == which &&Current_Board[i+1][j+1] == which &&Current_Board[i+2][j+2] == which &&Current_Board[i+3][j+3] == which)
				{
					Game_End_Flag = which;
					return;
				}
			}
			//��������
			for(i=0;i<Size-3;i++)
			{
				for(j=Size-1;j>Size-3;j-=1)
				if(Current_Board[i][j] == which &&Current_Board[i+1][j-1] == which &&Current_Board[i+2][j-2] == which &&Current_Board[i+3][j-3] == which)
				{
					Game_End_Flag = which;
					return;
				}
			}
		


	

	//������������֐��ɔ�΂�
			if(Game_End_Flag != 0 && Game_End_Flag != 1)
				Game_End_Flag = Game_Judge_Draw();

}

int Game_Judge_Draw()
{
	//���[�v����ϐ�
	int i,j;

	//�ՖʑS�Ă�����
	for(i=0;i<Size;i++)
	{
		for(j=0;j<Size;j++)
		{
			if(Current_Board[i][j] == -1)//�ЂƂł��󂫂�����΃Q�[�����s
				return 10;//Game_End_Flag�̏����l��Ԃ��Ă���

		}


	}

	//�S�đ����������ʋ󂪂Ȃ��ꍇ(-1���ЂƂ��Ȃ�)���������������l��Ԃ�
	return -1;

}

//CPU`���C��
//4���Ԏ�A�h����A�~�j�}�b�N�X�@�̏��Ŏ�����߂�
int CPU_Turn(int which)
{
	int Number =  -1;//CPU���̎�(�����l�Ŏ�Ƃ��Ăӂ��킵���Ȃ��l�����Ă���)
	int i,j;//���[�v����ϐ�

	//�肪���肳��Ă��Ȃ��ꍇ
	if(CPU_Decision == 0)
	{
		//4���Ԏ�CPU���P���ɏ��ꏊ��T��
		Number = Find_Vic_Def_Point(1);
		
		if(Number != -1)
		{
			//�肪���肵����t���O�Z�b�g���Ă���
			CPU_Decision = 1;
		}

	}
	
	if(CPU_Decision == 0 )
	{
		
		//���Ԃ��Ƃ�h����(����(��)���u���ď��ꏊ��T���A�����Ɏ����̌��̐F��u���Ėh�����ƂƂ���)
		Number = Find_Vic_Def_Point(0);
				
		if(Number != -1)
		{
			//�肪���肵����t���O�Z�b�g���Ă���
			CPU_Decision = 1;
			//�h���ꍇ�A�����t���O��10�ɖ߂��Ă���
			Game_End_Flag = 10;
		}

	}

	if(CPU_Decision == 0)
	{

	
		//�~�j�}�b�N�X
		
		/*------------------------------------------------------------------------*/
		//�m�[�h0�̏�����
		Use_Game_Tree[0].State_Number = 0;//�J�ڐ�m�[�h�z�񐧌�ϐ�������
		Use_Game_Tree[0].This_Node_Depth = 0;//�[������������
		Use_Game_Tree[0].This_Node_Parent = -1;//�J�n�m�[�h�̐e�͖����Ƃ�-1�ŕ\��
		//�m�[�h0��Current_Board�����R�s�[
		for(i=0;i<Size;i++)
		{
			for(j=0;j<Size;j++)
			{
				Use_Game_Tree[0].This_Node_Board_Info[i][j] = Current_Board[i][j];
			}
		}
		/*------------------------------------------------------------------------*/


		//�Q�[���؍쐬
		Create_Child_Node(0);



		//�~�j�}�b�N�X�@���s
		Number = Min_Max();
	
		//�肪���肵����t���O�Z�b�g���Ă���
		CPU_Decision = 1;

		//������ߏI������烁�����͊J�����Ă���
	//	free(Use_Game_Tree);
	
	}


		//���Ԃ�
		return Number;



}

//�e�m�[�h����q�m�[�h���萔�̐������W�J����֐�
int Create_Child_Node(int Parent_Node_Number)
{
	int i,j;


	//���̐[���̓W�J�J�n�m�[�h�ԍ����Z�o����(�V�����[���ɓ˓��������߂̈��ڂ���
	if(Next_Node_Flag == 0)
	{
		Next_Parent_Node = Parent_Node_Number + pow((double)Size,(double)Current_Depth);
	//	printf("Next Parent:%d\n",Next_Parent_Node);
		Next_Node_Flag = 1;//���b�N
	}

	//�ד��m�̃m�[�h�ԍ��������e�������ǂ����𔻒�
	//�قȂ�ΐ[���̋�؂�ƂȂ�A�I�����肪����
	if(Parent_Node_Number > 0
		&& Use_Game_Tree[Parent_Node_Number - 1].This_Node_Parent != Use_Game_Tree[Parent_Node_Number].This_Node_Parent
		 && Current_Depth == Depth)
	{

	//		printf("�I��\n");

			return 0;



	}else{

		//�ד��m�̃m�[�h�������e�������A�܂��[�����B���Ă��Ȃ��ꍇ�A�q�m�[�h���炳��ɐ[���W�J����
		
			//�e�m�[�h���畝�D��I�Ɏ萔�����m�[�h��W�J����
			for(i=0;i<Size;i++)
			{
				//�m�[�h�W�J�e���t�����K�{
				Node_Number++;
				//�e�m�[�h�̑J�ڐ���X�V
				Use_Game_Tree[Parent_Node_Number].State_Node[Use_Game_Tree[Parent_Node_Number].State_Number] = Node_Number;
				Use_Game_Tree[Parent_Node_Number].State_Number++;
				//�W�J���ꂽ�q�ɏ��ǉ��Ə�����
				Use_Game_Tree[Node_Number].This_Node_Parent = Parent_Node_Number;
				Use_Game_Tree[Node_Number].State_Number = 0;
				Use_Game_Tree[Node_Number].This_Node_Depth = Current_Depth + 1;
				//printf("%d\n",Use_Game_Tree[Node_Number].This_Node_Depth);
				for(j=0;j<Size;j++)
				{
					//�J�ڐ�m�[�h�ԍ���-1�ŏ��������Ă���
					Use_Game_Tree[Node_Number].State_Node[j] = -1;
				}
				
				//�쐬�����m�[�h���̎��o��
		//		printf("�쐬�m�[�h%d\n�e�m�[�h%d\n�J�ڎ�%d\n",Node_Number,Parent_Node_Number,i);
				//���݂̔Ֆʂ̃R�s�[
				Board_Copy(Node_Number);
				//���̃m�[�h�̔Ֆʏ��\�z�ƕ\��
				if(Current_Depth % 2 != 0)//�[����Ŕ��u��
				{
					Create_Board(i,1,Node_Number);

				}else{

					Create_Board(i,0,Node_Number);

				}
			}


			//�e�̐؂�ւ��|�C���g
			if(Parent_Node_Number != Next_Parent_Node - 1)
			{
			//���̐e�m�[�h�������������Ă���
				Use_Game_Tree[Parent_Node_Number + 1].State_Number = 0;
				Create_Child_Node(Parent_Node_Number + 1);
			
			}else{
				
	
				Current_Depth++;
				Next_Node_Flag = 0;//�t���O���Z�b�g
				//�m�[�h��񏉊�������
				
				Use_Game_Tree[Next_Parent_Node].State_Number = 0;
				Create_Child_Node(Next_Parent_Node);
		
			}



		}


	return 0;
}

//�]���֐�����:�F�i1:��0:���j:�]���l�����߂�m�[�h�ԍ�:�Ֆʃ��x���̉�:�Ֆʃ��x���̏c
int Evaluation_Fanction(int which,int node_number,int Board_Label_Wide,int Board_Label_Height)
{

	int Collor_Count = 1;
	//�u���ꂽ�ꏊ�𒆐S�ɐ^�������7�ߖT�ɑ΂��A�����F���������邩������

	//�{�[�h���x��11(B)�����Ώ�
	if(Board_Label_Wide != Size - 1)
	{
		//�E��
		if(Use_Game_Tree[node_number].This_Node_Board_Info[Board_Label_Height - 1][Board_Label_Wide + 1] == which)
		{
			Collor_Count += 1;
		}
		//�E
		if(Use_Game_Tree[node_number].This_Node_Board_Info[Board_Label_Height][Board_Label_Wide + 1] == which)
		{
			Collor_Count += 1;
		}
		//�E��
		if(Use_Game_Tree[node_number].This_Node_Board_Info[Board_Label_Height + 1][Board_Label_Wide + 1] == which)
		{
			Collor_Count += 1;
		}

	}

	//�X�^�b�N�|�C���^1�ȏ�Ώ�
	if(Board_Label_Height > 0)
	{
		//��
		if(Use_Game_Tree[node_number].This_Node_Board_Info[Board_Label_Height + 1][Board_Label_Wide] == which)
		{
			Collor_Count += 1;
		}

	}

	//�{�[�h���x��1�ȏ�Ώ�
	if(Board_Label_Wide != 0)
	{
		//����
		if(Use_Game_Tree[node_number].This_Node_Board_Info[Board_Label_Height + 1][Board_Label_Wide - 1] == which)
		{
			Collor_Count += 1;
		}
		//��
		if(Use_Game_Tree[node_number].This_Node_Board_Info[Board_Label_Height][Board_Label_Wide - 1] == which)
		{
			Collor_Count += 1;
		}
		//����
		if(Use_Game_Tree[node_number].This_Node_Board_Info[Board_Label_Height - 1][Board_Label_Wide - 1] == which)
		{
			Collor_Count += 1;
		}

	}

	//�u��������ɂ��������F������������Ԃ�
	return Collor_Count;


}



//�~�j�}�b�N�X�@:�������̐e�m�[�h�ԍ�:�ǂ������������ԂɂȂ��Ă��邩
int Min_Max()
{
	//���[�v����ϐ�
	int i,j;
	int Start_Node_Number = 1;//�ő�[���̍ŏ��m�[�h�ԍ�
	int Node_Number_Temp = 0;//�]���l���i�[���邽�߁A�m�[�h�ԍ����ꎞ�ۑ����Ă���
	int Current_Parent;//���ݕ]���l�����߂Ă���e�̃m�[�h�ԍ�
	int Node[Game_Tree_Size];//�m�[�h�̍ő吔���̔z���e��(�O�̂��ߓ��I�m��)
	int Comp_Node_Number = 0;
	int Comp_Node_Ev = 0;
	int Sarch_Depth = Depth;//�]���l�����߂�q�̐[��
	int Sarch_Node_Number;//Comp_Node_Number+1���i�[���A���[�v�̊J�n�l���w�肷��

	//step1:�ő�[���̍ŏ��m�[�h�ԍ����擾
//	printf("Step1\n");
	while(1)
	{
		if(Use_Game_Tree[Start_Node_Number].State_Node[0] != -1)
		{
			Start_Node_Number = Use_Game_Tree[Start_Node_Number].State_Node[0];

		}else{
//			printf("�ő�[���̍ŏ��m�[�h�ԍ�%d\n",Start_Node_Number);
			break;
		}
	}

	//step2:�e�m�[�h�ԍ����擾
//	printf("Step2\n");
	Current_Parent = Use_Game_Tree[Start_Node_Number].This_Node_Parent;

	while(1)
	{

	//step0:������
	for(i=0;i<Game_Tree_Size;i++)
	{
		//�m�[�h�z���-1�ŏ��������Ă���
		Node[i] = -1;

	}

	//step3:�e�m�[�h�̎q�m�[�h�̕]���l��Node�z��Ɋi�[
//	printf("Step3\n");
	for(i=0;i<Size;i++)
	{
		//�e�m�[�h����e�J�ڐ�m�[�h�ԍ����ꎞ�m��
		Node_Number_Temp = Use_Game_Tree[Current_Parent].State_Node[i];
		//�J�ڐ�m�[�h�̕]���l��Node�z��Ɋi�[
		Node[Node_Number_Temp] = Use_Game_Tree[Node_Number_Temp].This_Node_Evaluation_Value;

	}

	//step4:Node�z��𓪂��猩�čs���A�ŏ��ɗv�f��-1�ȊO�ƂȂ����Ƃ��A�m�[�h�ԍ��ƕ]���l���i�[����
//	printf("Step4\n");
	for(i=0;i<Game_Tree_Size;i++)
	{
		if(Node[i] != -1)
		{
			//�m�[�h�ԍ��Ƃ��̕]���l���L�����Ă���
			Comp_Node_Number = i;
			Comp_Node_Ev = Node[i];
			break;

		}

	}

	//step5:��r���� �m�[�h�Q�̕]���l�ōő�(�������͍ŏ�)�̂��̂�T��
	//�[���������A���̂ЂƂ����̃m�[�h�Q����͍ő�̂��̂��Ƃ�
	//�[������A���̂ЂƂ����̃m�[�h�R����͍ŏ��̂��̂��Ƃ�
//	printf("Step5\n");
	Sarch_Node_Number = Comp_Node_Number + 1;
	for(i=Sarch_Node_Number;i<Game_Tree_Size;i++)
	{

		//�[���������̈ʒu�ɂ���m�[�h�Q����͍ŏ��̂��̂�T���o��(Node[i]��-1�͒l���i�[����Ă��Ȃ�)
		if(Sarch_Depth % 2 == 0)
		{
			if(Node[i] < Node[Comp_Node_Number] && Node[i] != -1)
			{
				Comp_Node_Number = i;
				Comp_Node_Ev = Node[i];

			}

		}else if(Sarch_Depth % 2 != 0 && Node[i] != -1){
			//�[������̈ʒu�ɂ���m�[�h�Q����͍ő�̂��̂�T���o��
			if(Node[i] > Node[Comp_Node_Number])
			{
				Comp_Node_Number = i;
				Comp_Node_Ev = Node[i];

			}


		}


	}
	//step6 ���߂�ꂽ�ő�i�ŏ��j�]���l�����m�[�h�̕]���l���A�e�m�[�h�̕]���l�ɏ���������
//	printf("Step6\n");
	Use_Game_Tree[Use_Game_Tree[Comp_Node_Number].This_Node_Parent].This_Node_Evaluation_Value
		= Use_Game_Tree[Comp_Node_Number].This_Node_Evaluation_Value;
	//printf("�m�[�h%d�̕]���l��%d�ƌ��肵�܂���\n",Use_Game_Tree[Comp_Node_Number].This_Node_Parent
	//	,Use_Game_Tree[Comp_Node_Number].This_Node_Evaluation_Value);

	
	if(Use_Game_Tree[Comp_Node_Number].This_Node_Parent == 0)
	{
	//	printf("�I��\n");
		//���܂����]���l����A���T��
		for(i=0;i<Size;i++)
		{
			if(Use_Game_Tree[0].This_Node_Evaluation_Value ==  Use_Game_Tree[i].This_Node_Evaluation_Value)
			{
				//���Ԃ�
				return i;

			}
		}

		break;

	}



	//step7 �e�m�[�h���X�V�����̓����[���ʒu�ɂ���e�m�[�h�̕]���l�����߂ɍs��
	//���̐e�͑O�̐e�Ɠ����m�[�h��e�m�[�h�������ǂ���
	if(Use_Game_Tree[Current_Parent].This_Node_Depth == Use_Game_Tree[Current_Parent + 1].This_Node_Depth)
	{
		Current_Parent = Current_Parent + 1;

	}else{
		//���̐[���̈�ԎႢ�m�[�h�ԍ�(���[���Z�o)
		Start_Node_Number = 0;
		for(i=0;i<Sarch_Depth - 1;i++)
		{
			Start_Node_Number += pow((double)Size,(double)i);

		}
		Sarch_Depth -= 1;
		Current_Parent = Use_Game_Tree[Start_Node_Number].This_Node_Parent;
	
	}

	}

    



	//�Ō�ɋ��߂����Ԃ�
	return;

	
	
}

//�e�m�[�h�̔Ֆʍ\�z(���u)
void Create_Board(int position, int which,int node_number)
{
	//position:�u���ꏊ
	int i,j;

	//�m�[�h�\���̂̔Ֆʏ��ɔ���u��
	for(i=0;i<Size;i++)
	{
		if(Use_Game_Tree[node_number].This_Node_Board_Info[i][position] != -1)
		{
			if(which == 0)
			{
				//���u��
				Use_Game_Tree[node_number].This_Node_Board_Info[i-1][position] = 0;
				//�u�����炻�̏ꏊ����]���l�����߁A�\���̗v�f�Ɋi�[����
				Use_Game_Tree[node_number].This_Node_Evaluation_Value = 
					 Evaluation_Fanction(which,node_number,position,i-1);
				break;

			}else if(which == 1){
				//���u��
				Use_Game_Tree[node_number].This_Node_Board_Info[i-1][position] = 1;
				//�u�����炻�̏ꏊ����]���l�����߁A�\���̗v�f�Ɋi�[����
				Use_Game_Tree[node_number].This_Node_Evaluation_Value = 
					 Evaluation_Fanction(which,node_number,position,i-1);
				break;

			}
		}else if(i == Size-1){
		//�u���ꏊ�ɉ����u����Ă��Ȃ��Ƃ��A��ԉ��ɒu��
			if(which == 0)
			{
				//���u��
				Use_Game_Tree[node_number].This_Node_Board_Info[Size-1][position] = 0;
				//�u�����炻�̏ꏊ����]���l�����߁A�\���̗v�f�Ɋi�[����
				Use_Game_Tree[node_number].This_Node_Evaluation_Value = 
					 Evaluation_Fanction(which,node_number,position,Size-1);
				break;
			
			}else if(which == 1){
				//���u��
				Use_Game_Tree[node_number].This_Node_Board_Info[Size-1][position] = 1;
				//�u�����炻�̏ꏊ����]���l�����߁A�\���̗v�f�Ɋi�[����
				Use_Game_Tree[node_number].This_Node_Evaluation_Value = 
					 Evaluation_Fanction(which,node_number,position,Size-1);
				break;
			
			}
		
		}

	}
	/*
	//�����I������Ֆʕ\���f�o�b�O

	for(i = 0;i<Size;i++)
	{
		for(j = 0;j<Size;j++)
		{

			if(Use_Game_Tree[node_number].This_Node_Board_Info[i][j] == 0)
			{
				printf("0");
			}else if(Use_Game_Tree[node_number].This_Node_Board_Info[i][j] == 1)
			{

				printf("X");
			}else{

				printf(".");
					
			}

		}

		printf("\n");

	}
	*/

	//���x���\��
//	printf("0123456789AB\n");
	//�]���l�\��
//	printf("�]���l:%d\n",Use_Game_Tree[node_number].This_Node_Evaluation_Value);


}
//�e�m�[�h�̔Ֆʏ����q�m�[�h�ɃR�s�[
int Board_Copy(int node_number)
{
	int i,j;
	

	for(i=0;i<Size;i++)
	{

		for(j=0;j<Size;j++)
		{
			Use_Game_Tree[node_number].This_Node_Board_Info[i][j] = 
				Use_Game_Tree[Use_Game_Tree[node_number].This_Node_Parent].This_Node_Board_Info[i][j];
			
		}

	}


}

//�ЂƂu�����Ƃ��A���A�������͑��肪3������Ă���Ƃ����Ԃ�(����:�u���F ��:1 ��:0)
int Find_Vic_Def_Point(int which)
{
	int BP = -1;//�{�[�h�|�C���^�[
	int i,j;//���[�v����ϐ�


	for(i=0;i<Size;i++)
	{
		BP = -1;//������
		for(j=0;j<Size;j++)
		{
			//�Ֆʂ�����-1�ȊO�̂Ƃ���ɂȂ����Ƃ��A���̈���BP�Ƃ���
			if(Current_Board[j][i] != -1)
			{
				BP = j;
				BP--;
				break;
			}



		}
		//�����̒i�K��BP��-1�̏ꍇ�A��ԉ���11�ɒu���悤�ɂ���
		if(BP == -1)
		{
			BP = 11;
		}

		Current_Board[BP][i] = which;
		Game_Judge(which);//�u�����Ƃ������������ǂ���
		if(Game_End_Flag == 0 || Game_End_Flag == 1)//���Ă΂��̈ʒu
		{
			//�����̏ꍇ�A���Ԃ�
			return i;
		}else{//�u���Ă������ĂȂ�
		//printf("0�͏�����ł͂Ȃ�\n");//�����Ȃ��ꍇ������0���炂�܂ŕ\�������(�b��)
		}
		Current_Board[BP][i] = -1;//��x�u�������߂�
	}

	//���ꏊ���Ȃ��ꍇ-1��Ԃ��Ă���
	return -1;


}













