//      tiantai.c ��̨
inherit ROOM;

void create()
{
	set("short", "��̨");
	set("long", @LONG
������ѩɽ�µĸߴ������߿ɼ���ΰ�Ĵ�ѩɽ���ϱ�
���Ը�������羵��ʥ����
LONG );
	set("exits", ([
		"west" : __DIR__"neidian",
	]));
	setup();
}

