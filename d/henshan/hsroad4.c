// Room: /d/henshan/hsroad4.c ����·
// Modified by Java on Feb.14.1998

inherit ROOM;

void create()
{
	set("short", "����·");
	set("long", @LONG
������һ����������Ļ���·�ϣ���������ɭɭ�����֡����治Զ
���Ǻ����س��ˡ�����������һ�������
LONG );
	set("outdoors", "hengyang");

	set("exits", ([
		"east"  : __DIR__"hengyang1",
		"west"  : __DIR__"hsroad5",
	]));

	setup();
}
