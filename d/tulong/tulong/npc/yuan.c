#include <ansi.h>
inherit NPC;
void create()
{
	set_name("Ԫ�㲨", ({ "yuan guangbo", "yuan", "guangbo" }) );
	set("long", "���Ǻ�ɳ���ܶ���Ԫ�㲨��Ŀ����磬��ı뺴��\n");
	set("attitude", "heroism");
	set("title", HIY "��ɳ���ܶ���" NOR);
	set("age", 15);

	set("max_neili", 1000+random(500));
	set("combat_exp", 800000);

	set_skill("unarmed", 100+random(50));
	set_skill("parry", 100+random(50));
	set_skill("dodge", 100+random(50));
	set_skill("force", 100+random(50));

	set("max_qi", 2500+random(1000));
	set("max_jing", 2500+random(1000));

	setup();

	carry_object("/d/beijing/npc/obj/cloth6")->wear();
}

int accept_fight(object who)
{
	command("say �Ҳ���������ֻ�����(bi)һЩ�Һ�ɳ��ľ�����");
	return 0;
}

int accept_hit(object who)
{
	command("say �Ҳ���������ֻ�����(bi)һЩ�Һ�ɳ��ľ�����");
	return 0;
}

int accept_kill(object who)
{
	command("say ��ô������������ͷǵ�Ҫ���ײ��ɣ�");
	return notify_fail("ɲ�Ǽ�����û��ǲ�Ҫ�������Ϊ�á�\n");
}

int accept_ansuan(object who)
{
	return notify_fail("����밵�㣬����ֻ���᳡���ѹѹ�ļ������ˣ��������������\n");
}

int begin()
{
	object me=this_player();
	if (!me->query_temp("bishi", 1))
		//return 0;
            return notify_fail("����Ⱥͳ��������ԣ�Ȼ���������ҡ�"NOR"\n");
	if (objectp(present("chang jinpeng",environment())))
	return 0;

	command("grin");	
	command("say �Һ�ɳ��ľ���������ʹ�ö��κ��ˣ�������Ҹ���һ�룬��Σ�");

	message_vision(HIW "$N������װ�������붾�Σ�$N��$n����һ�롣"NOR"\n",
			   this_object(),me);

	me->set_temp("bi",1);
	set("anti",me);
	me->apply_condition("duyan",random(4)+1);
	this_object()->apply_condition("duyan",random(10)+10);
	return 1;
}

void die()
{
	if (objectp(query("anti")))
	{
		command("say ��������......");
		message_vision(HIR "\n$N˻����ɤ�Ӹɺ���������˫�۷��ף������ڵأ������³�һЩ��ĭ������Ҳû���ˡ�"NOR"\n",
				   this_object());
		query("anti")->set_temp("win_yuan",1);
		query("anti")->delete_temp("bi");
	}
	::die();
}

void unconcious()
{
	if (objectp(query("anti")))
	{
		command("say ��������......");
		message_vision(HIR "\n$N˻����ɤ�Ӹɺ���������˫�۷��ף������ڵأ������³�һЩ��ĭ������Ҳû���ˡ�"NOR"\n",
				   this_object());
		query("anti")->set_temp("win_yuan",1);
		query("anti")->delete_temp("bi");
	}
::die();
}

void init()
{
	add_action("do_get","get");
	add_action("begin","bi");
}

int do_get(string arg)
{
	object obj,env,ding;
	string what,where;
	if(!arg) return 0;
	if (objectp(obj=present("chang jinpeng",environment(this_object())))) return 0;
	if(sscanf(arg,"%s from %s",what, where) !=2) return 0;
	obj=this_object();

	if(what == "tulong blade"||what == "blade"||what == "dao"||what == "tulong" || where =="ding")
	{
		message_vision(CYN "$N�ȵ����޳�С��������ס�֣���ƾʲô�ô˱�����"NOR"\n",
				   obj,this_player());

		message_vision(CYN "$N�����˵����Ҫ�ô˵����ȱ�(bi)Ӯ������˵��"NOR"\n",
				   obj,this_player());

		this_player()->delete_temp("bi");
		return 1;
	}
	return 0;
}

