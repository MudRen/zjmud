//Room: /d/dali/hongsheng1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","����");
	set("long",@LONG
��ʥ��������ϵ��ʯ�����ɣ���ǧѰ����Ϊש����ͬ��������
�������ţ��������ʵǶ��ϡ�
LONG);
	set("exits",([ /* sizeof() == 1 */
	    "out"    : __DIR__"hongsheng",
	    "up"     : __DIR__"hongsheng2",
	]));
	set("no_clean_up", 0);
	setup();
}

int valid_leave(object me, string dir)
{
	int c_skill;

	me = this_player();

	if (dir == "up" )
	{
		c_skill = (int)me->query_skill("dodge", 1);
		if (me->query("qi") > 40)
		{
			me->receive_damage("qi", 20 + random(20));
			if (me->can_improve_skill("dodge") && c_skill < 100)
				me->improve_skill("dodge", 1 + c_skill / 15);
			tell_object(me,"������һ��¥����Щ���ˡ�\n");
		} else
		{
			me->set("qi", 0);
			tell_object(me,"�������������ˡ�\n");
			return -1;
		}
	}
	return 1;
}
