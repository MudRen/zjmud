#include <ansi.h>
inherit NPC;

void create()
{
	object jing,dao;
	set_name("������", ({ "chang jinpeng", "chang" }) );
	set("long", "�������ӥ����ȸ̳��̳����������\n"
		    "��ʮ������ͣ��������ϵļ��ⰼ��͹͹���̸���ڡ�\n");
	set("attitude", "heroism");
	set("title", "��ӥ��");
	set("nickname", HIR "��ȸ̳̳��" NOR);
	set("age", 52);
	set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		"�������ȵ��������������֣�\n",
		"�������ȵ���������������\n",
		(: perform_action, "hammer.poli" :),
	}) );

	set("per", 20);
	set("str", 45);
	set("int", 45);
	set("con", 45);
	set("dex", 45);
	
	set("max_qi", 5500);
	set("max_jing", 2000);
	set("neili", 6000);
	set("max_neili", 6000);
	set("jiali", 200);
	set("combat_exp", 2000000);

	set_skill("force", 200+random(50));
	set_skill("longxiang", 200+random(50));
	set_skill("dodge", 200+random(50));
	set_skill("shenkong-xing", 200+random(50));
	set_skill("cuff", 200+random(50));
	set_skill("yujiamu-quan", 200+random(50));
	set_skill("hand", 200+random(50));
	set_skill("dashou-yin", 200+random(50));
	set_skill("parry", 200+random(50));
	set_skill("hammer", 200+random(50));
	set_skill("riyue-lun", 200+random(50));

	map_skill("force", "longxiang");
	map_skill("dodge", "shenkong-xing");
	map_skill("cuff", "yujiamu-quan");
	map_skill("hand", "dashou-yin");
	map_skill("parry", "riyue-lun");
	map_skill("hammer", "riyue-lun");

	prepare_skill("hand", "dashou-yin");
	prepare_skill("cuff", "yujiamu-quan");

	set_temp("apply/attack", 80+random(80));
	set_temp("apply/defense", 80+random(80));
	set_temp("apply/armor", 80+random(80));
	set_temp("apply/damage", 80+random(80));

	setup();

	carry_object("/d/tulong/tulong/npc/obj/jiaofu")->wear();
	carry_object("/d/tulong/tulong/npc/obj/hammer")->wield();
	
	dao = find_object("/d/tulong/obj/tulongdao");
	jing = find_object("/d/tulong/obj/zhenjing");

	if (clonep()&&(!dao||!environment(dao)) && (!jing||!environment(jing))) {
		if(!dao) dao = load_object("/d/tulong/obj/tulongdao");
		dao->move(this_object());
	}
}

int accept_ansuan(object who)
{
	return notify_fail("����밵�㣬����ֻ���᳡���ѹѹ�ļ������ˣ��������������\n");
}

void init()
{
	object env;
	add_action("do_bi","bi");
	add_action("do_get","get");
	remove_call_out("put");
	call_out("put",3);
}

void put()
{
	object obj,obj2, *ob_list;
	obj = present("tulong blade",this_object());
	obj2 = present("ding", environment());
		
	if (	!obj && !present("tulong blade", obj2) )
	{
		message_vision(HIC "\n$N����һЦ���������������ˣ����������ѱ��������ˡ���"NOR"\n", this_object());
	}
	else
	if (objectp(obj) && objectp(obj2)) 
	{
		obj->move(obj2);
		message_vision(HIC "\n$N����һЦ����һ�ӣ��������������������������Ĵ������С�"NOR"\n",this_object());
	}
	obj = present("tulong blade",this_object());
	if (objectp(obj)) destruct(obj);
}

int do_get(string arg)
{
	object obj = this_object();
	string what, where;

	if(!arg)
	return 0;	
	if(sscanf(arg, "%s from %s", what, where) != 2)
	return 0;

	if(what == "tulong blade"||what == "blade"||what == "dao"||what == "tulong" || where =="ding")
	{
		message_vision(CYN "$N��$n���һ�����󵨣����Ҵ򱦵������⣡"NOR"\n",obj,this_player());

		message_vision(CYN "$N��$n�ȵ����ȹ�����һ�ء�"NOR"\n",obj,this_player());
		if (!obj->query_temp("bishi"))
		{
			obj->set_temp("bishi", 1);
			this_player()->set_temp("bishi", 1);
		}
            if (!this_player()->query_temp("bishi")) this_player()->set_temp("bishi", 1);
		obj->kill_ob(this_player());
		this_player()->kill_ob(obj);
		return 1;
	}

	return 0;
}

int do_bi()
{
	object obj = this_object();
	message_vision(CYN "$N��$n���һ���������Ǿͱ��Ա��ԣ����ɡ�"NOR"\n",obj,this_player());
      if (!this_player()->query_temp("bishi")) this_player()->set_temp("bishi", 1);
	obj->kill_ob(this_player());
	this_player()->kill_ob(obj);
	return 1;
}

int accept_fight(object me)
{
	object obj = this_object();
	command("say �����̵ģ�Ҫ����������������⣡\n");
	this_player()->kill_ob(obj);
	kill_ob(me);
	return 1;
}

int accept_hit(object me)
{
	object obj = this_object();
	command("say �����̵ģ�Ҫ����������������⣡\n");
	this_player()->kill_ob(obj);
	kill_ob(me);
	return 1;
}

int accept_kill(object me)
{
	object obj = this_object();
	command("say �����̵ģ�Ҫ����������������⣡\n");
	this_player()->kill_ob(obj);
	kill_ob(me);
	return 1;
}
