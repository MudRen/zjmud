// Room: /d/fuzhou/wuyishan4.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������Ϊ������ʤ������������Ϊ�����������֡�ɽ������
���ۡ��Ҳ�Ϊ���¼�Ʒ�����������⡣
LONG );
	set("exits", ([
		"southeast" : __DIR__"wuyishan5",
	]));
	set("outdoors", "fuzhou");
	setup();
}

