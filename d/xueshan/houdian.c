//      houdian.c ���

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
������ѩɽ�µĺ�Ҳ��ѩɽ���ӱ��������ĵط���
������һЩ���������ź�ľ�ˣ�����һЩ�����ŵ�ɳ����
ֱ����ľ׮��
LONG );

	set("exits", ([
		"south" : __DIR__"neidian",
	]));

	set("objects", ([
		"/clone/npc/mu-ren" : 1,
	]));

	setup();
}
