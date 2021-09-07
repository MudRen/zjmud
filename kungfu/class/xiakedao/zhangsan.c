// zhangsan.c

#include <ansi.h>

inherit NPC;

int is_punisher() { return 1; }

void create()
{
	set_name("����", ({ "zhang san", "zhang", "san" }));
	set("title", HIY "���͵�����ʹ��" NOR);
	set("gender", "����");
	set("age", 37);
	set("long",
	      "���Ǹ���������ʮ����ĺ��ӣ���ķ��֣���ɫ����\n"
	);

	set("str", 36);
	set("int", 35);
	set("con", 34);
	set("dex", 37);

	set_temp("apply/armor", 1500);
	set_temp("apply/damage", 800);
	set_temp("apply/unarmed_damage", 800);

	set("qi", 9000);
	set("max_qi", 9000);
	set("jing", 20000);
	set("max_jing", 20000);
	set("neili", 85000);
	set("max_neili", 85000);
	set("jiali", 500);
	set("combat_exp", 50000000);
	set("score", 20000000);

	set_skill("force", 1200);
	set_skill("taixuan-gong", 1200);
	set_skill("dodge", 1200);
	set_skill("taixuan-gong", 1200);
	set_skill("unarmed", 1200);
	set_skill("taixuan-gong", 1200);
	set_skill("parry", 1200);
	set_skill("martial-cognize", 1200);
	set_skill("count", 1200);

	map_skill("force", "taixuan-gong");
	map_skill("dodge", "taixuan-gong");
	map_skill("unarmed", "taixuan-gong");
	map_skill("parry", "taixuan-gong");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: perform_action, "unarmed.taixuan" :),
	}) );
	create_family("���͵�", 0, "����ʹ��");
	setup();

	carry_object("/clone/misc/cloth")->wear();
}

void start_punish(object ob, string msg)
{
	set_temp("punish_ob", ob);
	move(environment(ob));
	message_vision("$N���˹���������Ķ���$n��\n", this_object(), ob);
	command("chat " + ob->name() + "����" + msg);
	command("chat " + "������" + name() + "ҪΪ���ֳ�ȥ�˺���");
	command("follow " + ob->query("id"));

	if (environment(ob)->query("no_fight"))
	{
		tell_object(ob, "�㿴��" + name() + "���������в���һ����ת�����ߡ�\n");
		message("vision", ob->name() + "����" + name() + "����ɫ���䣬ת�����ߡ�\n" +
			name() + "��Цһ�������������ߡ�\n",
			environment(ob), ({ ob }));
		ob->move("/d/city/guangchang");
		move("/d/city/guangchang");
		tell_object(ob, HIR "...��...�����������Ϥ����"
			    "���ĵ�һ�ᣬת�����������Բ������ˡ�"NOR"\n");
		message("vision", ob->name() + "�Ż����ŵ����˹�����ֻ����һ��"
			"������������\n", environment(ob), ({ ob }));
	}

	kill_ob(ob);
	command("yun powerup");
}

void killed_enemy(object victim)
{
	command("chat �ٺ٣���Ҳ����һ�죬��ͽ������Ʊ������ж񱨣����ǲ�����ʱ��δ����");
	victim->delete("combat/need_punish");
}

varargs int receive_damage(string type, int damage, object who)
{
	return ::receive_damage(type, damage / 300, who);
}

varargs int receive_wound(string type, int wound, object who)
{
	return ::receive_wound(type, wound / 300, who);
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	ob->receive_wound("qi", 300 + random(200), me);
	me->set("neili", me->query("max_neili"));
	return HIR "$N" HIR "����һ����������Ϯ�������$n"
	       HIR "�����˺󼸲����ƺ�һ����"NOR"\n";
}

void unconcious()
{
	die();
}

void die()
{
	object ob;

	ob = query_temp("punish_ob");
	if (objectp(ob) && ob == query_last_damage_from())
		ob->delete("combat/need_punish");

	command("chat ���ģ��벻����" + name() + "��������...��������...�Ȼ�ȥ����ȥ��");
	message_vision(HIM "$N" HIM "���¼�����Ѫ������һ��������"
		       HIM "���Ż��������ˡ�\n", this_object());
	destruct(this_object());
}

void scan()
{
	object ob;

	if (! environment())
	{
		destruct(this_object());
		return;
	}

	if (! objectp(ob = query_temp("punish_ob")) ||
	    environment(ob) != environment() ||
	    environment(ob)->query("no_fight"))
	{
		command("chat �����������ˣ����������������");
		message_vision("$N������Ц��ƮȻ��ȥ��\n", this_object());
		destruct(this_object());
		return;
	}

	if (! is_fighting(ob))
		kill_ob(ob);

	::scan();
}
