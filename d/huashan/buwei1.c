// buwei1.c

inherit ROOM;

void create()
{
	set("short", "������Ϊ��");
	set("long", @LONG
���ǻ�ɽ��������Ⱥ�ľ�����������Ϊ�������˴���ǰ�������Ϲ���
�������á������Ҷ���кܿ���ȴûʲô���裬��ǽ�������ѽ��Σ�
����������Ⱥ���¡���ͽ�ĵط������������ҡ�
LONG );
	set("exits", ([ /* sizeof() == 2 */
	    "north" : __DIR__"buwei2",
	    "south" : __DIR__"qunxianguan",
	    "west"  : __DIR__"garden",
	    "east"  : __DIR__"buwei3",
	]));
	set("objects", ([
	     __DIR__"npc/dayou": 1,
	     __DIR__"npc/little_monkey": 1,
	]) );

	setup();
}

int valid_leave(object me, string dir)
{
    object guarder;

    if (objectp(guarder = present("lu dayou", this_object())) &&
	dir == "north")
    {
	if (! guarder->permit_pass(me, dir))
	{
	    return notify_fail("½���кȵ��������Ǽ�"
			       "ʦ���ң���λ" + RANK_D->query_respect(me) +
			       "��ֹ����\n");
	}
    }

    return 1;
}
