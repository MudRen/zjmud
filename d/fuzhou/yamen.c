// Room: /d/fuzhou/yamen.c
// Date: may 12. 1998 Java

inherit ROOM;

void create()
{
	set("short", "�ᶽ����");
	set("long", @LONG
���������Ŵ��ţ�������ľ���Ž����ر��š����ྲ��
���رܡ������ӷַ���ͷʯʨ�ӵ��Աߡ�ǰ����һ����ģ�
������ʲ��վ����ǰ��
LONG );
	set("exits", ([
		"east" : __DIR__"nandajie",
	]));
	set("objects", ([
		__DIR__"npc/geshiha" : 1,
	]));
	set("no_fight", 1);
	setup();
}

int valid_leave(object me, string dir)
{
	object ob;

	if (objectp(ob = present("ge shiha", environment(me))) &&
	    dir != "east" && living(ob))
		return notify_fail("��ʲ���ȵ�����ʩ������ȥУ���ı��������θɣ���\n");

	return ::valid_leave(me, dir);
}
