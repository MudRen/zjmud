//ROOM: /d/yanziwu/kuxiu2.c

inherit ROOM;

void create()
{
	set("short", "���޳�");
	set("long",@LONG
����ĳ�����Щ���䣬��Ȼ������ɨ�����ǳ�����Ȼ���ó����ٺ�
����ϣ������ͷ�ص�Ľ�ݼҵ������书����һ������Ϊ�Ժ�����������
������һ�������С������м���һЩͭ���������ˣ�����һЩͭ�塣
LONG );
	set("outdoors", "yanziwu");
	set("exits", ([
		"west" : __DIR__"kuxiu",
	]));

	set("objects", ([
		"/clone/npc/tong-ren" : 3,
	]));

	set("for_family", "Ľ������");
	setup();
}
