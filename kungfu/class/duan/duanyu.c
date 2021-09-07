// duanyu.c ����

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("����", ({"duan yu", "duan", "yu"}));
	set("gender", "����");
	set("age", 22);
	set("long", "����һ�����������������ӡ������Լ⣬��һ�������Ĵ�����\n");
	set("attitude", "peaceful");
	set("class", "royal");
	
	set("str", 21);
	set("int", 36);
	set("con", 32);
	set("dex", 29);

	set("chat_chance", 1);
	set("chat_msg", ({
		"����̾�˿��������������ϰ�������ô���£���\n",
	}));

	set("inquiry", ([
		"����" : "�����Ǹ��õط���ɽ��ˮ�㣬�羰���ˡ�\n",
		"������" : "����������ֻ������磬������û���ҷ������\n",
		"��ʦ" : "��....���ҵ�ʦ�������ӡ����Ӻ�ׯ�ӣ����ǵ�ѧ���һ�ûѧȫ�ء�\n",
	]));

	set("qi", 5000);
	set("max_qi", 5000);
	set("jing", 2500);
	set("max_jing", 2500);
	set("neili", 9000);
	set("max_neili", 9000);
	set("jiali", 150);

	set("combat_exp", 1500000);

	set_temp("apply/damage", 50);
	set_temp("apply/defense", 50);

	set_skill("force", 240);		// �����ڹ�
	set_skill("beiming-shengong", 240);	// ��ڤ��
	set_skill("finger", 220);		// ����ָ��
	set_skill("six-finger", 220);		// ������
	set_skill("dodge", 250);		// ��������
	set_skill("lingbo-weibu", 250);		// �貨΢��
	set_skill("parry", 80);			// �����м�

	map_skill("force", "beiming-shengong");
	map_skill("dodge", "lingboweibu");
	map_skill("parry", "six-finger");
	map_skill("finger", "six-finger");

	prepare_skill("finger","six-finger");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "finger.six" :),
		(: perform_action, "finger.zhongheng" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/unarmed_damage", 150);

	setup();

	carry_object("/clone/misc/cloth")->wear();
}

void help_girl(object me)
{
	object wang;
	string msg;

	if (! living(this_object()))
		return;

	command("chat �������ӣ���Ҫ���ţ����Ҷ����ڴˣ�");

	switch (me->query("gender"))
	{
	case "����":
		msg = "��λ" + RANK_D->query_respect(me) +
		      "����������˺��ģ���ô���˵�������Ҳ�µ����֣�";
		break;
	case "Ů��":
		msg = "��λ" + RANK_D->query_respect(me) +
		      "����Ī�Ƕʼ��˼���ò�������´˶��֣�";
		break;
	default:
		msg = "��λ" + RANK_D->query_respect(me) +
		      "����˵����Ȼ���в�Ů����ô����Ů���ӵ����⣿";
		break;
	}	
	command("chat " + msg);

	if (wang = present("wang yuyan"))
	{
		if (living(wang))
			message_vision("$N��æ��ס$n���������$n�������ɣ�"
				       "�ҿ����书����������ָ������������\n",
				       this_object(), wang);
		else
			message_vision("$Nһ��§ס$n�����ڻ��С�\n",
				       this_object(), wang);

		me->remove_enemy(wang);
		wang->move(this_object());
		remove_call_out("check_enemys");
		call_out("check_enemys", 1, wang);
	}

	kill_ob(me);
}


int accept_fight(object me)
{
	command("say ��ѽѽ���л��ú�˵����Ҫ�Ͷ����");
	return 0;
}

int accept_hit(object me)
{
	command("say ��������ô���£���ôͻȻ�Ͷ��ִ����أ���");
	return 1;
}

int accept_kill(object me)
{
	command("say ���˷��ˣ�����ͷ��������û�У�");
	return 1;
}

void unconcious()
{
	object wang;

	command("chat ��������......");

	if (wang = present("wang yuyan", this_object()))
	{
		wang->move(environment());
		message_vision("$N��$n���ϵ�����������ʧɫ��������"
			       "�ɣ����ɣ�����ô������", wang, this_object());
	}

	::unconcious();
}

void die()
{
	object wang;

	if (wang = present("wang yuyan", this_object()))
	{
		wang->move(environment());
		message_vision("$N��$n���ϵ�����������ʧɫ��������"
			       "�ɣ����ɣ�����ô���˰���", wang, this_object());
	}

	::die();
}

void check_enemys(object wang)
{
	if (! objectp(this_object()) || ! objectp(wang))
		return;

	if (! living(this_object()))
		return;

	if (is_fighting() && random(5) == 0 && living(wang))
	{
		message_vision(HIC "��������$N�������ֹ�����˵Щ����"NOR"\n", this_object());
		add_temp("apply/damage", 10);
		add_temp("apply/defense", 10);
		receive_curing("qi", 300);
		receive_curing("jing", 150);
		receive_heal("qi", 300);
		receive_heal("jing", 150);
	}

	if (! is_fighting())
	{
		set_temp("apply/damage", 50);
		set_temp("apply/defense", 50);
		if (! living(wang))
		{
			command("say ���º��ˣ��ҵ��������Ӳ����ܾ��ˡ�");
			return;
		}
		message_vision("$n��$N�������ˣ��������ˣ��������ɡ�"
			       "$N��������İ�$n����������\n",
			       this_object(), wang);
		wang->move(environment(this_object()));
		return;
	}

	remove_call_out("check_enemys");
	call_out("check_enemys", 1, wang);
}
