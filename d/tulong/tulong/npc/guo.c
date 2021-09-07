#include <ansi.h>

inherit NPC;

void create()
{
	set_name("����ȭ", ({ "guo sanquan", "guo", "sanquan"}) );
	set("long",
		  "������ȭ�������˹���ȭ����ĸߴ�˫\n�ۼ����ʵ��һ����֪������Һ��֡�\n");
	set("attitude", "heroism");
	set("title", HIR "��ȭ��������" NOR);
	set("age", 56);
	set("combat_exp", 1000000);

	set_skill("unarmed", 200+random(50));
	set_skill("parry", 200+random(50));
	set_skill("dodge", 200+random(50));
	set_skill("force", 200+random(50));

	set("max_qi", 1000+random(500)); 
	set("max_jing", 1000+random(500)); 


	setup();

	carry_object("/d/beijing/npc/obj/cloth6")->wear();
}

int accept_fight(object who)
{
	command("say �Ҳ���������ֻ�����(bi)һЩȭ���ϵĹ���");
	return 0;
}

int accept_hit(object who)
{
	command("say �Ҳ���������ֻ�����(bi)һЩȭ���ϵĹ���");
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

int begin(object me)
{
	command("bow");
	command("say ���¶Բ�ס�ˣ��������粻����֮Σ���������ڸ���֮�֣�");
	command("say ����ȭ�ž���������ʹ�����Ϲ����ȳ�����ȭ��˵��");

	message_vision(HIR "\n$N�ȵ���С���ˣ������һȭ�ˡ��߽�Ϲǡ���"NOR"\n",
			   this_object());
	COMBAT_D->do_attack(this_object(), this_player(),query_temp("weapon"));

	message_vision(HIR "\n$N�ȵ����ã����ҵڶ�ȭ����ɽ��ʯ����"NOR"\n",
			   this_object());
	COMBAT_D->do_attack(this_object(), this_player(),query_temp("weapon"));

	message_vision(HIR "\n$N�ȵ�������ȭ���ˣ���ʽ��������ɨǧ����ֱ��������"NOR"\n",
			   this_object());
	this_object()->set_temp("apply/attack",250);
	this_object()->set_temp("apply/damage",250);
	COMBAT_D->do_attack(this_object(), this_player(),query_temp("weapon"));
	set("anti",me);
	me->set_temp("bi",1);
	if (me->query("max_neili")>2000) die();
	return 1;
}

void die()
{
	if (objectp(query("anti")))
	{
		message_vision(HIR "\n\n$Nһȭ�˶������Ļ�����$n" HIR
				   "��С����"NOR"\n",
				   this_object(),query("anti"));

		message_vision(HIR "�����С����������������$N" HIR
				   "��ȭʱ������ʯ����֪����ѿ�����Ѫ��"NOR"\n",
				   this_object(),query("anti"));

		query("anti")->set_temp("win_guo",1);
		query("anti")->delete_temp("bi");
	}
::die();
}

void init()
{
	add_action("do_get","get");
	add_action("do_bi","bi");
}

int do_get(string arg)
{
	object obj;
	string what,where;
	if(!arg) return 0;
	if (objectp(obj=present("mai jing",environment()))) return 0;
	if(sscanf(arg,"%s from %s",what, where) !=2) return 0;
	obj=this_object();
	if(what == "tulong blade"||what == "blade"||what == "dao"||what == "tulong" || where =="ding")
	{
		message_vision(CYN "$N����һ����"NOR"\n",
				   obj);
		message_vision(CYN "$N˵����Ҫ��õ��������ȹ�����ȭ��"NOR"\n",
				   obj);
		this_player()->delete_temp("bi");
		return 1;
	}
	return 0;
}

int do_bi()
{
	object me=this_player();
	if (!me->query_temp("bishi", 1))
		return 0;
	if (objectp(present("mai jing",environment()))) return 0;
	begin(me);
	return 1;
}

