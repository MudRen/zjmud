// road4.c ɽ·
inherit ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
������һ����ʯ��᾵�ɽ���ϣ����������ˮ��������ʯ������
�ұ������£�̧ͷ��Լ�ɼ������������е�ɽ�壬һ·����ɽ������
���ߡ�
LONG );
	set("outdoors", "xiakedao");
	set("exits", ([
		"southup" : __DIR__"pubu",
		"northdown" : __DIR__"road3",
	]));
	setup();
}

