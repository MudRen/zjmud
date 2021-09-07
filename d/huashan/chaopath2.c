// Room: chaopath2.c ������С·
//Date: Oct. 2 1997 by Venus
inherit ROOM;

void create()
{
      set("short","������С·");
      set("long",@LONG
�����ǳ�����С·��ɽ�ƶ��ͣ�����������ȣ�һ��С�Ķ����
����ȥ��������һ��С·������û����
LONG);
      set("outdoors", "xx");
      set("exits",([ /* sizeof() == 1 */
	  "southwest": __DIR__"chaopath1",
	  "eastup"   : __DIR__"chaoyang",
	  "westup"   : __DIR__"ziqitai",
      ]));
      set("objects", ([
	  __DIR__"npc/shi-daizi" : 1,
      ]));
      setup();
}
 
void init()
{
	object me = this_player();
	if (me->query_temp("xunshan")) me->set_temp("xunshan/chaoyang", 1);
	return;
}

int valid_leave(object me, string dir)
{
	if (dir != "eastup"  ||
	    ! objectp(present("shi daizi", environment(me))) ||
	    (me->query("family/master_id")!="gao laozhe") ||
	    (me->query("family/master_id")!="ai laozhe"))
		return ::valid_leave(me, dir);

	if (me->query("family/family_name") != "��ɽ��")
	{
		message_vision("ʩ����������ס$N��������Ǹ����������λ"
			       "��������֮������λ" + RANK_D->query_respect(me) +
			       "��ֹ����\n", me);
		return notify_fail("����ʩ���Ӳ��������ȥ��\n");
	}

	if (me->query("combat_exp") < 100000)
	{
		message_vision("ʩ����������ס$N������ֹ������������λ"
			       "��������֮��������Ȼ�Ǳ��ɵ��ӣ�����ѧ"
			       "�ղ��������ܰݼ���\n", me);
		return notify_fail("����ʩ���Ӳ��������ȥ��\n");
	}

	return ::valid_leave(me, dir);
}
