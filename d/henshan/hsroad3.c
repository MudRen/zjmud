// Room: /d/henshan/hsroad3.c ����·

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
������һ����������Ļ���·�ϣ���������ɭɭ�����֡����治Զ
���Ǻ����س��ˡ�
LONG );
	set("outdoors", "hengyang");

	set("exits", ([
		"northeast": __DIR__"hsroad2",
		"west"     : __DIR__"hengyang",
	]));

	setup();
}
