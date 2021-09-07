// feng.c ������

inherit NPC;
inherit F_MASTER;

#include <ansi.h>

// �Ž�
mapping po_type = ([ "�ƽ�ʽ" : ({ "sword" }),
		     "�Ƶ�ʽ" : ({ "blade" }),
		     "��ǹʽ" : ({ "staff" }),
		     "�Ʊ�ʽ" : ({ "hammer", "club", "dagger" }),
		     "����ʽ" : ({ "whip" }),
		     "����ʽ" : ({ "unarmed", "finger", "claw",
				   "strike", "hand", "cuff" }),
		     "�Ƽ�ʽ" : ({ "throwing" }),
		     "����ʽ" : ({ "force" }), ]);

int check_skill(string skill);
mixed teach_lonely_sword();

void create()
{
	set_name("������", ({ "feng qingyang", "feng", "qingyang" }));
	set("title", "��ɽ��ʮ�������ڳ���");
	set("long", @LONG
����ǵ������𽭺��Ļ�ɽ���޷�������������ۣ��������������
ֽ������ݳ���ü���һֱ������һ�ɵ�����������ɫ����Ȼ�Ե����
����֮��һֱ����������
LONG );
	set("gender", "����");
	set("age", 68);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 30);
	set("int", 40);
	set("con", 30);
	set("dex", 30);
	
	set("qi", 5500);
	set("max_qi", 5500);
	set("jing", 2600);
	set("max_jing", 2600);
	set("neili", 6800);
	set("max_neili", 6800);
	set("no_get", 1);
	set("jiali", 100);

	set("combat_exp", 2750000);
	set("score", 200000);

	set_skill("cuff", 240);
	set_skill("force", 250);
	set_skill("blade", 270);
	set_skill("dodge", 250);
	set_skill("parry", 270);
	set_skill("sword", 280);
	set_skill("strike", 240);
	set_skill("huashan-xinfa", 250);
	set_skill("zixia-shengong", 250);
	set_skill("poyu-quan", 240);
	set_skill("fanliangyi-dao", 270);
	set_skill("huashan-sword", 280);
	set_skill("hunyuan-zhang", 240);
	set_skill("lonely-sword", 280);
	set_skill("feiyan-huixiang", 250);
	set_skill("literate", 150);

	map_skill("cuff", "poyu-quan");
	map_skill("force", "zixia-shengong");
	map_skill("dodge", "feiyan-huixiang");
	map_skill("parry", "lonely-sword");
	map_skill("sword", "lonely-sword");
	map_skill("blade", "fanliangyi-dao");
	map_skill("strike", "hunyuan-zhang");

	prepare_skill("cuff", "poyu-quan");
	prepare_skill("strike", "hunyuan-zhang");

	create_family("��ɽǰ��", 0, "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.po" :),
		(: perform_action, "cuff.leidong" :),
		(: perform_action, "cuff.poshi" :),
		(: perform_action, "cuff.feng" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	set("no_teach", ([
		"lonely-sword"   : (: teach_lonely_sword :),
	]));

	set_temp("apply/attack", 220);
	set_temp("apply/defense", 220);
	set_temp("apply/damage", 200);
	set_temp("apply/unarmed_damage", 200);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}

mixed teach_lonely_sword()
{
	object me;

	me = this_player();
	if (me->query_skill("lonely-sword", 1) > 90)
	{
		if (me->query_temp("feng_has_told"))
		{
			command("say ���Լ��ú����ɣ�");
			return -1;
		}

		command("pat " + me->query("id"));
		command("say ��Ķ��¾Ž�Ҳ������Щ�ɾ��ˣ��⽣��Ҫ��"
			"�Լ��������Ժ����Լ�������аɣ�");
		me->set_temp("feng_has_told", 1);
		return -1;
	}

	if (me->query_temp("learnd_lonely_sword"))
		return 0;

	me->set_temp("learnd_lonely_sword", 1);
	command("say �ܺã����Ž������ڽ��⣬������ʽ����Ҫѧϰ���в�"
		"�ɾ�������ʽ��");
	return 0;
}

void attempt_apprentice(object ob)
{
	if (ob->query("family/family_name") == "��ɽ��" ||
	    ob->query("family/family_name") == "��ɽ����")
	{
		command("say �߿�����ɽ�ĵ�����һ�Ų�����");
		return;
	}

	command("say �Ҳ���ͽ������������ɡ�");
}

int check_skill(string skill)
{
	if (skill != "sword" && skill != "lonely-sword")
	{
		command("say �ٺ٣���ֻ������������ѧ��ѧ������ѧ�����ˡ�");
		return -1;
	}
	return 1;
}

int recognize_apprentice(object ob, string skill)
{
	if (ob->query("can_learn/feng/lonely-sword"))
		return check_skill(skill);

	if (ob->query("can_learn/feng/sword") &&
	    skill != "lonely-sword")
	{
		if (skill == "sword") return 1;
		command("say �������������ǿ������㣬�ٸ������£�");
		return -1;
	}

	if (ob->query_temp("have_asked_feng"))
	{
		command("say ���������");
		return -1;
	}

	if (ob->query("character") == "���ռ�թ" ||
	    ob->query("character") == "�ĺ�����")
	{
		command("heng");
		command("say �������ľ͸��ҹ���");
		ob->set_temp("have_asked_feng", 1);
		return -1;
	}

	if (ob->query("shen") < -1000)
	{
		command("say ��һ��аħ������ҷ�����û��Ȥ������"
			"���˴򽻵������߰ɡ�");
		ob->set_temp("have_asked_feng", 1);
		return -1;
	}

	if (ob->query("shen") > 10000)
	{
		command("haha");
		command("say �������Լ���·�ɣ������Ҳ�ʶʱ�񣬸���"
			"�����㣬�����ˡ�");
		ob->set_temp("have_asked_feng", 1);
		return -1;
	}

	if (ob->query("int") < 24)
	{
		message_vision("$N��Ц��������\n", this_object());
		command("say �������ͷ�죬߯���˵㣬�߰ɡ�");
		ob->set_temp("have_asked_feng", 1);
		return -1;
	}

	if (ob->query("int") < 30)
	{
		command("look " + ob->query("id"));
		command("say �㵹�ǲ��㱿���е�С����������... �ٺ٣�"
			"���ǲ��Զ����");
		ob->set_temp("have_asked_feng", 1);
		return -1;
	}

	if (ob->query_skill("sword", 1) < 60)
	{
		command("say �ҵ������Ľ���㶫����������ĶԽ�������"
			"��Ҳδ��̫���ˡ�");
		return -1;
	}

	if (ob->query("int") < 34)
	{
		if (skill == "sword")
		{
			command("say �ðɣ��Ҿͽ���һ����ڽ�����֪ʶ��");
			ob->set("can_learn/feng/sword", 1);
			return 1;
		}

		if (skill != "lonely-sword")
		{
			command("say ��ֻ�ὣ����Ҫѧ�����ı����ұ��ʦ��ȥ�ɣ�");
			return -1;
		}

		command("sigh");
		command("say ���������Ǵ�������������ô�����㻹�ǲ���"
			"ôһ����أ����¾Ž��㲻����ѧ��");
		return -1;
	}

	if (check_skill(skill) == -1)
		return -1;

	command("nod");
	command("say ��Ȼ�Ҳ���ͽ��������������ʵ�ڲ����ʹ���һ�㽣"
		"���ɡ�");
	command("say ���ȴ����ܾ�ʽ�������ƽ�ʽ���Ƶ�ʽ����ǹʽ���Ʊ�ʽ������ʽ������ʽ����"
		"��ʽ������ʽ�����һһ�ֽ���������");
	ob->set("can_learn/feng/lonely-sword", 1);
	return 1;
}

int accept_ask(object me, string topic)
{
	string *learned, *try_to;

	if (! topic || undefinedp(try_to = po_type[topic]))
		return 0;

	if (! (int)me->query_skill("lonely-sword", 1))
	{
		command("say ���"ZJURL("cmds:learn feng lonely-sword 100")"���¾Ž�"NOR"ô���������������");
		return 1;
	}

	learned = me->query("can_perform/lonely-sword");
	if (! arrayp(learned))
		learned = ({ });
	if (member_array(try_to[0], learned) != -1)
	{
		command("say �������������⼸����ʽ��
"ZJURL("cmds:ask feng qingyang about �ƽ�ʽ")"�ƽ�ʽ"NOR"��"ZJURL("cmds:ask feng qingyang about �Ƶ�ʽ")"�Ƶ�ʽ"NOR"��"ZJURL("cmds:ask feng qingyang about ��ǹʽ")"��ǹʽ"NOR"��"ZJURL("cmds:ask feng qingyang about �Ʊ�ʽ")"�Ʊ�ʽ"NOR"��
"ZJURL("cmds:ask feng qingyang about ����ʽ")"����ʽ"NOR"��"ZJURL("cmds:ask feng qingyang about ����ʽ")"����ʽ"NOR"��"ZJURL("cmds:ask feng qingyang about �Ƽ�ʽ")"�Ƽ�ʽ"NOR"��"ZJURL("cmds:ask feng qingyang about ����ʽ")"����ʽ"NOR"��
���" + topic + "�㲻���Ѿ�����ô���������Ҹ�ʲô��");
		return 1;
	}

	command("say �ðɣ�" + topic + "��Ҫ����Ҫ����ϸ�ˡ�");
	if (me->query("potential") - me->query("learned_points") < 10)
	{
		me->set("learned_points", me->query("potential"));
		tell_object(me, "������е��Ժ���û��̫�����������Լ���Ǳ�ܲ�����\n");
		return 1;
	}

	me->add("learned_points", 10);
	if (random(2))
	{
		write("������һ��������˵��ĵá�\n");
		return 1;
	}

	learned -= try_to;
	learned += try_to;
	me->set("can_perform/lonely-sword", learned);
	tell_object(me, HIG "��ѧ����" + topic + "��\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 360000);
	return 1;
}
