// Room: /d/songshan/chanyuan.c

inherit ROOM;

void create()
{
	set("short", "������Ժ");
	set("long", @LONG
������Ժ����ɽ������Ժ�йŰ�ɭɭ�����ϲ��޷���Ժ��
����������ǧ�ˡ�
LONG );
	set("exits", ([
		"southdown" : __DIR__"junjigate",
	]));
	set("objects", ([
		__DIR__"npc/zuo" :1,
		__DIR__"npc/shi" :1,
		__DIR__"npc/di" :1,
	]));
	setup();
}

