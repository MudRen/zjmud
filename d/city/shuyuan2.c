//Room: /d/city/shuyuan2.c

#define STORY_TOC "/doc/legend/toc"
inherit ROOM;

void create()
{
	set("short", "��Ժ���");
	set("long", @LONG
��������Ժ��ͼ��ݣ�����������һ����Ⱦ�����ϵ���ܶ��������ǵ���ѡ����һ����ͯ�����������
LONG);

	set("item_desc", ([ /* sizeof() == 1 */
		"����ܡ�" : "����һ����Ⱦ��ȫ�����Ӱټҵ��顣\n"
	]));

	set("exits", ([
	    "down" : __DIR__"shuyuan",
	]));

	set("no_fight", 1);
	set("no_sleep_room", 1);

	set("objects", ([
		__DIR__"npc/shutong" : 1,
	]));

	setup();
}

