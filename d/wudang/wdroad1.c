// wdroad1.c
// by Xiang

inherit ROOM;

void create()
{
	set("short", "��ʯ���");
	set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ������������Ҵ�
���������������һЩС��̯���ƺ���һ�����С�����ͨ�����ݳǡ�����
��һ��Ƭ���֡�
LONG );
	set("outdoors", "wudang");
	set("exits", ([
		"south"     : __DIR__"wdroad2",
		"north"     : "/d/city/nanmen",
	]));
	set("no_clean_up", 0);
	setup();
}

