
#include <ansi.h>

inherit COMBINED_ITEM;

string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIW"������"NOR, ({"ba gua"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("base_unit", "��");
		set("base_weight", 1);
		set("base_value", 2000);
		set("unit", "��");
		set("long","����һ�������̣��ܹ�ռ����ǰʦ������npc�ľ�ȷλ�ã�\n");
		set("only_do_effect", 1);
	}
	setup();
}


int do_effect(object me)
{
	object ob;
	mapping q;
	string area;

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
	}
	else
		tell_object(me,"�޷�ռ����Ŀ�����������Ŀ�������ѱ�ɱ��������ʧ�ˡ�\n");

	add_amount(-1);
	return 1;
}
