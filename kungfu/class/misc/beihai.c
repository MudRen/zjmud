// beihai.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("��������", ({ "king of dragon", "dragon" }) );
	set("title", HIC "����" NOR);
	set("gender", "����");
	set("age", 23);
	set("long", @LONG
����һ�����ˣ�üĿ֮��͸��һ�����ˡ�
LONG );
	set("combat_exp", 10000000);
	set("shen_type", 0);
	set("attitude", "heroism");
	set("max_neili", 20000);
	set("neili", 20000);
	set("max_jing", 20000);
	set("jing", 20000);
	set("max_qi", 25000);
	set("qi", 25000);
	set("jingli", 20000);
	set("max_jingli", 20000);

	set("str", 100);
	set("int", 30);
	set("con", 100);
	set("dex", 100);

	set_skill("unarmed", 1200);
	set_skill("sword", 1200);
	set_skill("parry", 1200);
	set_skill("dodge", 1200);
	set_skill("force", 1200);

	set("jiali", 200);

	set_temp("apply/attack", 300);
	set_temp("apply/unarmed_damage", 500);
	set_temp("apply/armor", 1000);

	if (clonep(this_object()))
	{
		set("chat_chance", 30);
		set("chat_msg", ({ (: random_move :) }));
		set("born_time", time());
		keep_heart_beat();
	}

	setup();
}

void fight_ob(object ob)
{
	if (is_fighting(ob))
		return;

	message_vision(HIC "$N" HIC "��ŭ��һ�����ȣ�����"
		       "��ʱѩ��ƮƮ��"NOR"\n", this_object(), ob);

	::fight_ob(ob);
	if (! is_killing(ob->query("id")))
		kill_ob(ob);
}

int accept_fight(object ob)
{
	message_vision("$N�ƺ�û������$n��˵ʲô��\n",
		       this_object(), ob);
	return 0;
}

int accept_kill(object ob)
{
	return 1;
}

int accept_hit(object ob)
{
	return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	ob->receive_wound("qi", 200 + random(200), me);
	me->set("neili", me->query("max_neili"));
	return HIC "$N" HIC "��������һ���³�һ�ں�������ʱ��$n"
	       HIC "��֫����������"NOR"\n";
}

void unconcious()
{
	die();
}

void die()
{
	object ob;

	ob = new("/clone/gift/cjade");
	command("chat ���ģ�����ͷ��������û��������ĵط��ˣ�");
	message_sort(HIC "$N" HIC "����һ����һ�������Ȼ�������������ۣ�ֻ��������һ��"
		     "���죬������һ" + ob->query("unit") +
		     ob->name() + HIC "��"NOR"\n", this_object());
	ob->move(environment());
	destruct(this_object());
}

void random_move()
{
	if (time() - query("born_time") > 1800)
	{
		message_vision("$N����ææ�����ˡ�\n", this_object());
		CHANNEL_D->do_channel(this_object(), "rumor",
			"��˵" + name() + HIM "���˼䷴ʡ���£���"
			"���ⷵ����硣" NOR);
		destruct(this_object());
		return;
	}
	NPC_D->random_move(this_object());
}
