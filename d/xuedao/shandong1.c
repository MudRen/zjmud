// shandong1.c
inherit ROOM;
void create()
{
	set("short", "ɽ��");
	set("long", @LONG
�տյ���һ��ɽ������Ҳ����ɾ�����ͷ����һ��ʯ����
LONG );
	set("exits", ([
		"out" : __DIR__"sroad8",
	]));
	set("objects", ([
		__DIR__"obj/dachang" :1,
	]));
	setup();
}

