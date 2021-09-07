#include <ansi.h>;
inherit NPC;
#include "/clone/fuben/npc/chinese.h";

void create()
{
	set_name("Ԫ��", ({"yuan bing",}));
	set("gender", "����");
	set("age", 35);
	set("long","Ԫ����\n");
	set("attitude", "peaceful");

	set("die_give", ([
		"/clone/weapon/blade" : 2,
	]));

	setup_family(0);
	setup();
}

void init()
{
	object ob;
	int sllv = environment()->query("sllv");
	int baselv = environment()->query("baselv");
	int baseqi = environment()->query("baseqi");

	init_skill(baselv+sllv*20);
	set("qi",baseqi+baselv*sllv/10);
	set("eff_qi",baseqi+baselv*sllv/10);
	set("max_qi",baseqi+baselv*sllv/10);
}

void die()
{
	int pot,exp;
	string str;
	int i;
	string *items;
	mapping give;
	object *t,obj;
	object me = this_object();
	object ob = me->query_last_damage_from();
	int sllv = environment(me)->query("sllv");

	t = ob->query_team();

	exp = (2*sllv*sllv+sllv*100);
	if(exp<100) exp=100;
	str = "һһһһһһһһһһһһһһһһһһһһһһһ\n"
		+sprintf(query("name")+"����һЩ�����Ǳ������ˡ�\nս��ʤ�������飺+%d,Ǳ�ܣ�+%d",exp,exp/2);

	for(i=0;i<sizeof(t);i++)
	{
		if(!present(t[i],environment(me)))
			continue;

		t[i]->add("combat_exp", exp);
		t[i]->add("potential", exp/2);
		t[i]->add("wanan", 1);
		tell_object(t[i],str+"\n");
	}

	if(give = query("die_give"))
	{
		items = keys(give);
		for(i=0;i<sizeof(items);i++)
		{
			if(random(give[items[i]])==0)
			{
				obj = new(items[i]);
				obj->move(environment(me));
			}
		}
	}
	destruct(me);
}
