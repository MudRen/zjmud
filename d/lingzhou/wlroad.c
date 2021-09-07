// Room: /lingzhou/wangling.c

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "����ͨ��");
	set("long", @LONG
������������Ĺ��ͨ������Ĺ����쳣���Ȼ��һ��ʯ����ʿ���������ȥ·��
LONG );
	set("exits", ([
		"south":__DIR__"qingxinquan",
	]));
	set("out_room",__DIR__"qingxinquan");
	set("objects", ([
	]));
	setup();
}

void heart_beat()
{
	object *inv;
	inv = all_inventory(this_object());
	if(!sizeof(inv)||(sizeof(inv)==1&&!playerp(inv[0])))
	{
		set_heart_beat(0);
		destruct(this_object());
	}
}

void no_die(object me)
{
	object ob;
	int num;

	if ( objectp(ob = present("wu shi",this_object())) )
	{
		num = time() - query("start_time");
		if(num>900) num = 900;
		num += 1000*(ob->query("max_qi")-ob->query("qi"))/ob->query("max_qi");
		if(num>0&&mapp(me->query("banghui")))
		{
			WARS_D->set_data("wangling/"+me->query("banghui/name")+"/pot",WARS_D->query_data("wangling/"+me->query("banghui/name")+"/pot")+num);
			tell_object(me,"��������Ϊ���ۣ��ڽ����������������Ϊ����������"+num+"�㹱�ף�\n");
		}
	}
}