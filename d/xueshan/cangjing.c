//      cangjingge.c �ؾ���
inherit ROOM;

void create()
{
	set("short", "�ؾ���");
	set("long", @LONG
������ѩɽ�µĲؾ�֮����������������ܶ�������
�伮����һ����Ҳ��������
LONG );
	set("exits", ([
		"northwest" : __DIR__"dating",
	]));
	set("objects", ([
		CLASS_D("xueshan")+"/lingzhi" : 1,
	]));

	setup();
}

