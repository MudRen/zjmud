inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIW"������"NOR, ({"ba gua"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 10000);
//		set("yuanbao", 200);
		set("no_shop", 1);
	 	set("u_times",5);
		set("unit", "��");
		set("long","����һ�������̣��ܹ�"ZJURL("cmds:use ba gua")ZJSIZE(20)"ռ��"NOR"��ǰʦ������npc�ľ�ȷλ�ã�����ʹ��5�Ρ�\n");
	}
}

void init()
{
    if (environment()==this_player())
    	add_action("on_used","use");
}

int on_used(string arg)
{
	object ob;
	object me=this_player();
	mapping q;
	string area;

	if (arg!="ba gua")
      		return notify_fail("��Ҫ��ʲô?\n");  

	if(!mapp(q=me->query("quest")))
	{
      		return notify_fail("������û������ʹ�ð�����ռ��ʲô?\n");  
	}
	if(q["type"]!="kill")
	{
      		return notify_fail("������û��ʦ��ɱ����������ռ����\n");  
	}
	if(ob=find_living(q["id"]))
	{
		sscanf(base_name(environment(ob)),"/d/%s/%*s",area);
                message_vision(HIW"$N�ӻ����ͳ�һ��"+name()+""HIW"���������˼���ͭǮ�����������дʣ���ʼ��ָϸ�㡣"NOR"\n" , me);
		tell_object(me,HIR+q["name"]+NOR"��"+q["id"]+"��Ŀǰ����"HIW+MAP_D->query_map_short(area)+NOR"��"HIW+environment(ob)->query("short")+NOR"���\n");

		add("u_times",-1);
		if(query("u_times")>0) tell_object(me,"��������̻�����ʹ��"+query("u_times")+"�Ρ�\n");
	}
	else
		tell_object(me,"�޷�ռ����Ŀ�����������Ŀ�������ѱ�ɱ��������ʧ�ˡ�\n");

	if(query("u_times")<=0){
	tell_object(me,"������Ű�������Ϊʹ�ô�������������ˡ�\n");
		destruct(this_object());
}

	return 1;
}
