// Room: /d/xiangyang/walln2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
���ǵ����ͷ��ʯ�ף���Ϊ��ǽ�ܸߣ����Ժܶ���ʯ����
���пɹ��������µ�б�µ���
LONG );
	set("outdoors", "xiangyang");
	set("exits", ([
		"westup"   : __DIR__"walln4",
		"eastdown" : __DIR__"northgate1",
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	int c_skill;

	me = this_player();
	if (sscanf(dir, "%*sup") == 1)
	{
		c_skill = me->query_skill("dodge", 1);
		if (me->query("qi") > 40)
		{
			me->receive_damage("qi", 20 + random(20));
			if (me->can_improve_skill("dodge") && c_skill < 100)
				me->improve_skill("dodge", 1 + random(me->query("dex")));
		} else
		{
			me->set("qi", 0);
			return notify_fail("��̫���ˣ�������Ϣһ����ɡ�\n");
		}
	}
	return 1;
}
