inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIR"����"NOR, ({"ba gua"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 100000);
//		set("yuanbao", 200);
		set("u_times",3);
		set("unit", "��");
		set("long","����һ�����ԣ�����"ZJURL("cmds:use ba gua")ZJSIZE(20)"ռ��"NOR"��ǰʦ������Ŀ��ľ�ȷλ��!\n");
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

	if (arg!="ba gua")
      		return notify_fail("��Ҫ��ʲô?\n");  

	if(!mapp(q=me->query("quest")))
	{
      		return notify_fail("������û������ʹ�ð��Դ���ʲô?\n");  
	}
	if(q["type"]!="kill")
	{
      		return notify_fail("������û��ʦ��ɱ�����������̽��\n");  
	}
	if(ob=find_living(q["id"]))
	{
		tell_object(me,q["name"]+"Ŀǰ����"+q["place"]+"��"+environment(ob)->query("short")+"���\n");
		add("u_times",-1);
	tell_object(me,"������Ի�����ʹ��"+query("u_times")+"�Ρ�\n");
	}

	if(query("u_times")<=0){
	tell_object(me,"���Ű�������Ϊʹ�ô�������������ˡ�\n");
		destruct(this_object());
}

	return 1;
}
