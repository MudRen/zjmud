// /guanwai/jishi.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����ǳ���һƬ�����Ĺ㳡�������������̽���ëƤ��ҩ���Լ�������
��ļ��С����ڸ�����Բ���������ôһ�����У�������������࣬����
Ҳ��ȫ����ͬ�ķ��Σ���ͬ�����Զ����������￴�������������ҵ���Ⱥ��
��������ߺ�ȣ�������������
LONG );
	set("exits", ([
		"north" : __DIR__"beicheng",
		"south" : __DIR__"nancheng",
		"east"  : __DIR__"dongcheng",
		"west"  : __DIR__"kedian",
	]));
	set("objects", ([
		__DIR__"npc/pihuoshang" : 3,
		__DIR__"npc/hadani" : 1,
	]));
	set("outdoors", "guanwai");
	setup();
}

