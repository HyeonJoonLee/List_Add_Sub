#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <iostream> // C++ ����� �Լ� ���
#include <string>   // C++ ���ڿ� ���



//Ÿ�� ����
typedef struct { int degree;  float coef[100]; } poly1;
typedef struct { float coef;  int exp; } poly2;
typedef struct poly3 {
	float coef;  int exp;    struct poly3* link;
} poly3;


typedef struct student
{
	int no; char name[10]; int k; int e; int m; int tot; float ave;
} student;

typedef struct student2
{
	int no; char name[10]; int k; int e; int m; int tot; float ave;
	struct student2* link; //���� ����ü�� �ּҸ� �����ϴ� ���
} student2;



//�Լ� ����
void score(int k[], int e[], int m[], int t[], float a[])
{
	for (int i = 0; i < 3; i++)
	{
		t[i] = k[i] + e[i] + m[i];
		a[i] = t[i] / 3.0;
	}
}
//���׽� �����ϴ� �Լ�
void add(poly1* PA, poly1* PB, poly1* PC)
{
	int deg_A, deg_B;
	int Apos, Bpos, Cpos;
	Apos = Bpos = Cpos = 0;
	deg_A = PA->degree;  deg_B = PB->degree;

	if (deg_A > deg_B) PC->degree = deg_A;
	else               PC->degree = deg_B;

	while (Apos <= PA->degree && Bpos <= PB->degree)
	{
		if (deg_A > deg_B)
		{
			PC->coef[Cpos++] = PA->coef[Apos++];
			deg_A--;
		}
		else if (deg_A < deg_B)
		{
			PC->coef[Cpos++] = PB->coef[Bpos++];
			deg_B--;
		}
		else //������ ���� ��
		{
			PC->coef[Cpos++] = PA->coef[Apos++] + PB->coef[Bpos++];
			deg_A--; deg_B--;
		}
	}
}

//���׽� �����ϴ� �Լ�
void sub(poly1* PA, poly1* PB, poly1* PD)
{
	int deg_A, deg_B;
	int Apos, Bpos, Dpos;
	Apos = Bpos = Dpos = 0;
	deg_A = PA->degree;  deg_B = PB->degree;

	if (deg_A > deg_B) PD->degree = deg_A;
	else               PD->degree = deg_B;

	while (Apos <= PA->degree && Bpos <= PB->degree)
	{
		if (deg_A > deg_B)
		{
			PD->coef[Dpos++] = PA->coef[Apos++];
			deg_A--;
		}
		else if (deg_A < deg_B)
		{
			PD->coef[Dpos++] = -PB->coef[Bpos++];
			deg_B--;
		}
		else //������ ���� ��
		{
			PD->coef[Dpos++] = PA->coef[Apos++] - PB->coef[Bpos++];
			deg_A--; deg_B--;
		}
	}
}

void calc(poly2 P[])
{
	int i, n;
	int As, Bs, Cs, Ae, Be;

	//�Է�
	std::cout << "���׽� A�� �� ���� : "; std::cin >> n;
	As = 0, Ae = As + n - 1;
	for (i = As; i <= Ae; i++)
		scanf_s("%f %d", &P[i].coef, &P[i].exp);

	std::cout << "���׽� B�� �� ���� : "; std::cin >> n;
	Bs = Ae + 1, Be = Bs + n - 1;
	for (i = Bs; i <= Be; i++)
		scanf_s("%f %d", &P[i].coef, &P[i].exp);

	Cs = Be + 1;

	//ȣ��(���)
	while (1)
	{
		if (As > Ae || Bs > Be) break;
		if (P[As].exp == P[Bs].exp) //�񱳵Ǵ� ���� ������ ������?
		{//A ��� + B��� --> C ���, ������ ����. As, Bs, Cs ����
			if (P[As].coef + P[Bs].coef == 0) { As++, Bs++; }
			else
			{
				P[Cs].coef = P[As].coef + P[Bs].coef;
				P[Cs].exp = P[As].exp;
				As++, Bs++, Cs++;
			}
		}
		else if (P[As].exp > P[Bs].exp) //A�� ������ �� ũ��?
		{ //A�� ���, ������ C�� ���� --> As, Cs ����
			P[Cs].coef = P[As].coef;
			P[Cs].exp = P[As].exp;
			As++, Cs++;
		}
		else // B�� ������ �� ũ��?
		{ //B�� ���, ������ C�� ���� --> Bs, Cs ����
			P[Cs].coef = P[Bs].coef;
			P[Cs].exp = P[Bs].exp;
			Bs++, Cs++;
		}
	}//ȭ�Ϲ� ��
	if (As > Ae) //���׽� B�� ���� ���� ���ұ���...
		for (i = Bs; i <= Be; i++)
		{ //B�� ���, ������ C�� ���� --> Bs, Cs ����
			P[Cs].coef = P[Bs].coef;
			P[Cs].exp = P[Bs].exp;
			Bs++, Cs++;
		}
	else if (Bs > Be) //���׽� A�� ���� ���� ���ұ���...
		for (i = As; i <= Ae; i++)
		{ //A�� ���, ������ C�� ���� --> As, Cs ����
			P[Cs].coef = P[As].coef;
			P[Cs].exp = P[As].exp;
			As++, Cs++;
		}

	//���
	std::cout << "\n ���׽� A = ";
	for (i = 0; i <= Ae; i++)
		printf(" %6.1fX%d ", P[i].coef, P[i].exp);

	std::cout << "\n ���׽� B = ";
	for (i = Ae + 1; i <= Be; i++)
		printf(" %6.1fX%d ", P[i].coef, P[i].exp);

	std::cout << "\n ���׽� C = ";
	for (i = Be + 1; i <= Cs - 1; i++)
		printf(" %6.1fX%d ", P[i].coef, P[i].exp);



}

void score2(student sss[])
{
	int i;
	for (i = 0; i < 3; i++)
	{
		sss[i].tot = sss[i].k + sss[i].e + sss[i].m;
		sss[i].ave = sss[i].tot / 3.0;
	}
}

poly3* link_add(poly3* X, poly3* Y, poly3* Z)  //���� ����ü�� �̿��� ���׽� ���� �Լ�
{
	poly3* p, * q, * r, * r2;
	p = X, q = Y;
	r = (poly3*)malloc(sizeof(struct poly3));
	Z = r2 = r;

	while (1)
	{
		if (p == NULL || q == NULL) break;
		if (p->exp == q->exp) //������ ������?
		{
			if (p->coef + q->coef != 0)
			{
				r->coef = p->coef + q->coef; r->exp = p->exp;
				r->link = NULL;  r2->link = r; r2 = r;
				r = (poly3*)malloc(sizeof(struct poly3));
			}
			p = p->link;  q = q->link;
		}
		else if (p->exp > q->exp)  //���׽� X�� ������ �� ũ��?
		{
			r->coef = p->coef; r->exp = p->exp;
			r->link = NULL; r2->link = r;  r2 = r;
			r = (poly3*)malloc(sizeof(struct poly3));
			p = p->link;
		}
		else if (p->exp < q->exp)  //���׽� Y�� ������ �� ũ��? 
		{
			r->coef = q->coef; r->exp = q->exp;
			r->link = NULL; r2->link = r;  r2 = r;
			r = (poly3*)malloc(sizeof(struct poly3));
			q = q->link;
		}
	}//ȭ�Ϲ� �� --> ���� �׵��� Z�� �ٿ��ֱ�
	if (p == NULL)
	{
		while (q != NULL)
		{
			r->coef = q->coef; r->exp = q->exp;
			r->link = NULL;  r2->link = r;  r2 = r;
			r = (poly3*)malloc(sizeof(struct poly3));
			q = q->link;
		}
	}
	else if (q == NULL)
	{
		while (p != NULL)
		{
			r->coef = p->coef; r->exp = p->exp;
			r->link = NULL;  r2->link = r;  r2 = r;
			r = (poly3*)malloc(sizeof(struct poly3));
			p = p->link;
		}
	}
	return Z;
}

void main()
{
	int i, menu, n;
	//�迭 7�� ����
	int no[3], k[3], e[3], m[3], t[3];
	float a[3];
	char name[3][10];

	//���׽� �迭�� ���� ����
	poly1  A, B, C, D;
	poly2  P[100]; //���׽� A, B, C�� �Ѳ����� ����
	//����ü�� ����ó���ϱ� ���� ����ü�迭 ���� ����
	student  st[3];
	student2* s, * p, * q;
	s = q = p = NULL;

	poly3* X, * Y, * Z, * a1, * b1, * c1, * c2;
	X = Y = Z = a1 = b1 = c1 = c2 = NULL;

	while (1) //���ѷ���
	{
		printf("\n\n\n �޴� 1)����ó��(�迭)  2)���׽�-1 ������  3)���׽�-2 ������");
		printf("4)����ó��  5)����ó��(���ᱸ��ü) 6)���׽� ������(���ᱸ��ü)   7)     8)����: ");
		scanf_s("%d", &menu);
		if (menu == 8) break;
		switch (menu) {
		case 1://�й�, �̸�, ��,��,�� �Է��ؼ� ����/��� ����� ���
			printf("�й�, �̸�, ��, ��, �� �Է� \n");
			for (i = 0; i < 3; i++)
			{
				printf("\n �й� : "); scanf_s("%d", &no[i]);
				printf("\n �̸� : "); std::cin >> name[i];
				printf("\n ���� : "); scanf_s("%d", &k[i]);
				printf("\n ���� : "); scanf_s("%d", &e[i]);
				printf("\n ���� : "); scanf_s("%d", &m[i]);
				printf("\n");
			}
			score(k, e, m, t, a);
			printf("\n �й�, �̸�, ��, ��, ��, ����, ���  \n");
			for (i = 0; i < 3; i++)
			{
				printf(" %3d %10s %3d %3d %3d %3d %5.1f \n",
					no[i], name[i], k[i], e[i], m[i], t[i], a[i]);
			}
			break;
		case 2://���׽� 2�� �Է�, ���, ��� ���׽� ���
			printf("\n ���׽� A�� ���� : "); scanf_s("%d", &A.degree);
			printf("\n ���׽� A�� ��� : ");
			for (i = 0; i <= A.degree; i++)
				scanf_s("%f", &A.coef[i]);
			printf("\n ���׽� B�� ���� : "); scanf_s("%d", &B.degree);
			printf("\n ���׽� B�� ��� : ");
			for (i = 0; i <= B.degree; i++)
				scanf_s("%f", &B.coef[i]);

			// ���׽� ����
			add(&A, &B, &C); //�μ��� ����ü ������ CBR ����
			// ���׽� ����
			sub(&A, &B, &D);

			//���
			printf("\n ���׽� A = ");
			for (i = 0; i <= A.degree; i++)
				printf("%.1fX%d + ", A.coef[i], A.degree - i);
			printf("\n ���׽� B = ");
			for (i = 0; i <= B.degree; i++)
				printf("%.1fX%d + ", B.coef[i], B.degree - i);
			printf("\n ������ ���׽� C = ");
			for (i = 0; i <= C.degree; i++)
				printf("%.1fX%d + ", C.coef[i], C.degree - i);
			printf("\n ������ ���׽� D = ");
			for (i = 0; i <= D.degree; i++)
				printf("%.1fX%d + ", D.coef[i], D.degree - i);
			break;
		case 3://poly2 ����ü�� �̿��Ͽ� ���׽� ������ ����
			calc(P);
			break;
		case 4:
			printf("�й�, �̸�, ��, ��, �� �Է� \n");
			for (i = 0; i < 3; i++)
			{
				printf("\n �й� : "); std::cin >> st[i].no;
				printf("\n �̸� : "); std::cin >> st[i].name;
				printf("\n ���� : "); std::cin >> st[i].k;
				printf("\n ���� : "); std::cin >> st[i].e;
				printf("\n ���� : "); std::cin >> st[i].m;
				printf("\n");
			}
			score2(st);

			printf("\n �й�, �̸�, ��, ��, ��, ����, ���  \n");
			for (i = 0; i < 3; i++)
			{
				printf(" %3d %10s %3d %3d %3d %3d %5.1f \n",
					st[i].no, st[i].name, st[i].k, st[i].e,
					st[i].m, st[i].tot, st[i].ave);
			}
			break;
		case 5://�ڱ����� ����ü�� ����ó��
			p = (student2*)malloc(sizeof(student2));
			s = q = p;
			while (1)
			{
				printf("\n �й� : "); std::cin >> p->no;
				if (p->no < 0) break;
				printf("\n �̸� : "); std::cin >> p->name;
				printf("\n ���� : "); std::cin >> p->k;
				printf("\n ���� : "); std::cin >> p->e;
				printf("\n ���� : "); std::cin >> p->m;
				p->tot = p->k + p->e + p->m;
				p->ave = p->tot / 3.0;
				// �Է��� ���������� ����� ��츦 ���� ���� ���� 3���� 
				p->link = NULL; //������ ����ü�� �ļ� ����ü�� �����Ƿ� null�� ó�� 
				q->link = p;    // ��� ������ ����ü �ּ� ����
				q = p;          //q�� p�� ����
				p = (student2*)malloc(sizeof(student2)); //����ü ���� �Ҵ�
			}

			//���
			p = s;
			while (1)
			{
				if (p == NULL) break;
				printf("\n %3d %10s %3d %3d %3d %3d %7.1f",
					p->no, p->name, p->k, p->e, p->m, p->tot, p->ave);
				p = p->link;
			}
			break;
		case 6://���� ����ü�� �̿��Ͽ� ���׽� ������ �ϱ�
			//���׽� X �Է�
			std::cout << "\n ���׽� A �Է�(��� ���� : ��� -999 �Է��ϸ� ����)";
			a1 = (poly3*)malloc(sizeof(struct poly3));
			X = b1 = a1;
			while (1)
			{
				std::cout << "\n ��� : ";  std::cin >> a1->coef;
				if (a1->coef == -999) break;
				std::cout << "\n ���� : ";  std::cin >> a1->exp;
				a1->link = NULL;  b1->link = a1;  b1 = a1;
				a1 = (poly3*)malloc(sizeof(struct poly3));
			}

			//���׽� Y �Է�
			std::cout << "\n ���׽� B �Է�(��� ���� : ��� -999 �Է��ϸ� ����)";
			a1 = (poly3*)malloc(sizeof(struct poly3));
			Y = b1 = a1;
			while (1)
			{
				std::cout << "\n ��� : ";  std::cin >> a1->coef;
				if (a1->coef == -999) break;
				std::cout << "\n ���� : ";  std::cin >> a1->exp;
				a1->link = NULL;  b1->link = a1;  b1 = a1;
				a1 = (poly3*)malloc(sizeof(struct poly3));
			}
			//���
			Z = link_add(X, Y, Z);

			//���׽� X ���
			a1 = X;
			std::cout << "\n\n ���׽� A = ";
			while (1)
			{
				if (a1 == NULL) break;
				std::cout << a1->coef << "X" << a1->exp << "  ";
				a1 = a1->link;
			}
			//���׽� Y ���
			a1 = Y;
			std::cout << "\n\n ���׽� B = ";
			while (1)
			{
				if (a1 == NULL) break;
				std::cout << a1->coef << "X" << a1->exp << "  ";
				a1 = a1->link;
			}
			//���׽� Z ���
			a1 = Z;
			std::cout << "\n\n ���׽� C = ";
			while (1)
			{
				if (a1 == NULL) break;
				std::cout << a1->coef << "X" << a1->exp << "  ";
				a1 = a1->link;
			}

			break;
		default: printf("\n �޴����� ����. �ٽ� �����Ͻÿ�...\n\n");
		}
	}
}