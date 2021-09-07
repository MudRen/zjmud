#include <ansi.h>

#define LVYU_ZHANG    "/clone/weapon/green_stick"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

int try_to_learn_ds();
int try_to_learn_db();
mixed ask_me();
mixed ask_bang();

void create()
{
	set_name("���߹�", ({"hong qigong", "hong", "qigong"}));
	set("nickname", "��ָ��ؤ");
	set("gender", "����");
	set("age", 75);
	set("long", 
		"������ؤ���ʮ���ΰ������ųơ���ؤ���ĺ��߹���ү�ӡ�\n");
	set("attitude", "peaceful");
	set("str", 37);
	set("int", 31);
	set("con", 33);
	set("dex", 32);
	set("chat_chance", 1);
	set("chat_msg", ({
		"���߹�̾�˿�����������������ʱ���ٳԵ��ض����ġ��л�������������\n",
		"���߹�˵�������׻�˵�����ڽ��ϡ��������Ͻл��ص��������ݿ�������\n",
		"���߹��૵���������ؤ��ġ�����ʮ���ơ���������Ե����Ʒ�����\n",
	}));
	set("chat_chance_combat", 1);
	set("chat_msg_combat", ({
		(: perform_action, "strike.xianglong" :),
		(: exert_function, "recover" :),
	}) );
	set("inquiry", ([
		"�����޹�" : (: ask_me :),
		"�򹷰�"  : (: ask_bang :),
	]));
	set("qi", 5200);
	set("max_qi", 5200);
	set("jing", 2700);
	set("max_jing", 2700);
	set("neili", 7000);
	set("max_neili", 7000);
	set("jiali", 120);
	set("combat_exp", 2500000);
	set("score", 50000);

	set_skill("force", 270);
	set_skill("jiaohua-neigong", 250);
	set_skill("huntian-qigong", 270);
	set_skill("unarmed", 230);
	set_skill("changquan", 230);
	set_skill("dodge", 240);
	set_skill("xiaoyaoyou", 240);
	set_skill("feiyan-zoubi", 240);
	set_skill("parry", 250);
	set_skill("staff", 270);
	set_skill("strike", 270);
	set_skill("dragon-strike", 270);
	set_skill("jiaohua-bangfa", 250);
	set_skill("dagou-bang", 270);
	set_skill("throwing", 220);
	set_skill("mantianhuayu-zhen", 220);
	set_skill("begging", 200);
	set_skill("checking", 200);
	set_skill("training", 180);
	map_skill("throwing", "mantianhuayu-zhen");
	map_skill("force", "huntian-qigong");
	map_skill("unarmed", "changquan");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("parry", "changquan");
	map_skill("staff", "dagou-bang");
	map_skill("strike", "dragon-strike");

	prepare_skill("strike", "dragon-strike");

	set("no_teach", ([
		"dragon-strike" : (: try_to_learn_ds :),
		"dagou-bang"    : (: try_to_learn_db :),
	]));

	create_family("ؤ��", 17, "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "staff.wugou" :),
		(: perform_action, "staff.ban" :),
		(: perform_action, "staff.chan" :),
		(: perform_action, "strike.leiting" :),
		(: perform_action, "strike.xiang" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();
	carry_object(__DIR__"yuzhu_zhang")->wield();
}

int accept_object(object who, object ob)
{
	int r;
	int lv;
	string by;
	object me;
	string hid;
	object hob;

	if (r = ::accept_object(who, ob))
		return r;

	me = this_object();

	if (! ob->query("food_supply"))
	{
		command("say ����������ɶ��");
		return -1;
	}

	if (! intp(lv = ob->query("level")) ||
	    lv < 1 || ! stringp(by = ob->query("by")))
	{
		command("say �ⶫ������ȥҲûɶ�ر�ģ����Ը����Űɡ�");
		return -1;
	}

	if (lv < 100)
	{
		message_vision("$N���˿�" + ob->name() + "�������ᣬ��ü��������... "
			       "�㻹���Ը����Űɣ���\n", me);
		return -1;
	}

	if (lv < 180)
	{
		message_vision("$N������$n�ݹ�����" + ob->name() + "��˵������ζ����"
			       "�񲻴�������������΢Ƿ��ôһ���������\n", me, who);
		return -1;
	}

	message_vision("$N������$n�ݹ�����" + ob->name() + "�����˼��ڣ�ֱ����ͷ��̾"
		       "��������... �ü��ˣ���\n", me, who);
	destruct(ob);
	if (! who->id(by))
	{
		message_vision("$N�ֵ�������ϧѽ����ϧ����֪������˭��"
			       "�ģ��п���ɵø���������������\n", me);
		return 1;
	}

	if (who->query("gender") != "Ů��")
	{
		message_vision("$N������$n��Ц�������벻����һ������ү������"
			       "Ҳ�����ѵã��ѵã���\n", me, who);
		return 1;
	}

	if (! stringp(hid = who->query("couple/id")))
	{
		message_vision("$N���˿�$n��Ц������" + RANK_D->query_repsect(who) +
			       "��������ż���û�У���Ҫ�ҽ��ܣ���\n", me, who);
		return 1;
	}

	if (who->query("static/marry") > 1)
	{
		message_vision("$N����һ�������������ϧ������ɷ�Ĺ�ϵ�Ѿ��������ˣ���Ȼ��"
			       "���ǿ��Դ������ֹ������Ǳ��𡣡�\n", me);
		return 1;
	}

	if (! objectp(hob = find_player(hid)))
	{
		message_vision("$N����һ�������������ϧ����λ���ڣ���Ȼ��"
			       "���ǿ��Դ������ֹ������Ǳ��𡣡�\n", me);
		return 1;
	}

	message_vision("$N����һЦ���������ܺã��Ͻл�ûʲôֵǮ�ģ�ʲôʱ"
		       "������λ���ˣ��ҽ��������Ʒ��ɣ���\n", me, who);
	hob->set("can_learn/hong/dragon-strike", 1);
	hob->set("can_learn/hong/staff", 1);
	who->set("can_learn/hong/xiaoyaoyou", 1);
	who->set("can_learn/hong/staff", 1);
	tell_object(who, HIG + me->name() + HIG "��Ӧ����" +
			 hob->name(1) + "����ʮ���Ʒ��ͻ����ȷ���Ϊ����"NOR"\n");
	tell_object(who, HIG + me->name() + HIG "��Ӧ����" +
			 who->name(1) + "��ң�κͻ����ȷ���Ϊ����"NOR"\n");
	return 1;
}

int recognize_apprentice(object me, string skill)
{
	if (me->query("gender") != "����") 
	{
		if (skill != "xiaoyaoyou" && skill != "staff")
		{
			command("say ������ѧ�����ʲô����ʲôʱ��˵�������ˣ�"); 
			return -1; 
		}

	} else
	{
		if (skill != "dragon-strike" && skill != "strike" && 
		    skill != "staff")
		{
			command("say ������ѧ�����ʲô����ʲôʱ��˵�������ˣ�"); 
			return -1; 
		}
	}

	if (! me->query("can_learn/hong/" + skill))
	{
		command("say �ٺ�... ����ѧ�书... �������˰ɣ��Ͻл�����ͽ��"); 
		return -1;
	}
	return 1;
}

int try_to_learn_db()
{
	object me;

	me = this_player();
	if (me->query("can_learn/hong/dagou-bang"))
		return 0;

	if (me->query("beggarlvl") < 9)
	{
		command("say Ҳ����������ʲô���֣���Ȼ��ѧ�򹷰�����");
		return -1;
	}
	if (me->query("shen") < -1000)
	{
		command("say ����аħ������֮�������ѧϰ�񹦣�");
		return -1;
	}
	command("sigh");
	command("say �򹷰�������ֻ�������������������ڽ��������ң���"
		"Ҳ�Ǳ�����֣�ȴҲѧ֮�޷���");
	me->set("can_learn/hong/dagou-bang", 1);
	return 0;
}

int try_to_learn_ds()
{
	object me;
	object sob;
	int i;
	int flag;
	string *sub_skills;

	me = this_player();
	if (! me->query("can_learn/hong/dragon-strike") &&
	    me->query("beggarlvl") < 9)
	{
		command("say ��Ҫѧ����ʮ���ƣ������������������ﳤ����˵�ɣ�");
		return -1;
	}

	if (me->query("shen") < -1000)
	{
		command("say ��Ȼ����ؤ�ﲻ��ʲô��������������аħ��"
			"��̫�������ѧϰ�񹦣�");
		return -1;
	}

	sob = find_object(SKILL_D("dragon-strike"));
	if (! sob) sob = load_object(SKILL_D("dragon-strike"));
	if (! sob->valid_learn(me))
		return 0;
	if (me->query_skill("dragon-strike", 1))
	{
		command("say �㲻���Ѿ�����ô���Լ��ú����ɡ�");
		return -1;
	}

	sub_skills = keys(sob->query_sub_skills());
	flag = 0;
	for (i = 0; i < sizeof(sub_skills); i++)
	{
		if (me->query_skill(sub_skills[i], 1) >= 10)
			continue;
		me->set_skill(sub_skills[i], 10);
		if (! flag)
		{
			flag = 1;
			command("say �ã��Ҿͽ�ʮ��·�Ʒ��������㣬"
				"��Ҫ�ú���ϰ�����ձ����ڻ��ͨ��");
		}
		write(HIC "���" + to_chinese(sub_skills[i]) + "����һ"
		      "Щ����"NOR"\n");
	}

	if (! flag)
	{
		command("say ����˵�˴������ڻ��ͨ���������ֽ���");
		return -1;
	}

	command("say �ܺã�������ú��ù�������ʮ��·�Ʒ��ڻ��ͨ����"
		"��Ϊһ��˵�ɡ�");
	notify_fail("�ú�Ŭ�������¹���ɡ�\n");
	return -1;
}

void attempt_apprentice(object ob)
{
	if (ob->query("detach/ؤ��"))
	{
		command("say ��֪���գ��αص�����");
		return;
	}

	if (ob->query("betrayer"))
	{
		command("say С�ӣ���Ҫ�����ҿɾ�Ҫ����ʦ����ѵ��ѵ���ˣ�");
		return;
	}

	if (ob->query("family/family_name") != "ؤ��")
	{
		command("say �٣����Ȼ�Ѿ�������ʦָ�㣬�������Ͻл���ʲô��");
		return;
	}

	if (ob->query_str() < 40 && ob->query_int() < 42 && ob->query_con() < 40)
	{
		command("say ��˵���������Ҳ���У��Խ�Ҳ����⣬���ܺ���ѧʲô��");
	        tell_object(ob, "����������ǧ�ﴫ�������߹���ͽҪ�󲢲��ߣ��������߸�������һ��ﵽ40��������Դﵽ42��\n");
		return;
	}

	if ((int)ob->query_skill("force") < 200)
	{
		command("sigh");
		command("say ����ڹ����̫���ˣ��Ⱥú������������ҡ�");
		return;
	}

	if ((int)ob->query("max_neili") < 1000)
	{
		command("shake");
		command("say �����ǵ���������ѧ����ʲô�ϳ��书��");
		return;
	}
	command("recruit " + ob->query("id"));

	if((string)ob->query("class") != "beggar")
		ob->set("class", "beggar");
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/dagou-bang/wugou"))
		return "�úø�������ȥ�������Ҹ�ʲô��";

	if (me->query("family/family_name") != query("family/family_name"))
		return "��һ��ȥ��";

	if (me->query_skill("dagou-bang", 1) < 150)
		return "��Ĵ򹷰���ѧ����ô�������ҿ������Զ�أ�";

	message_vision(HIG "$n" HIG "���ֳ������һ����ʣ�µļ�"
		       "��ͷ������һ�����������ǹ���$N" HIG "��\n$P"
		       HIG "ֻ����ǰ" HIY "�ǹ�" HIG "��㣬����������һ��"
		       "ɱ��������������"NOR"\n",
		       me, this_object());
	command("say �㿴����û�У�");
	tell_object(me, HIG "��ѧ���������޹���"NOR"\n");
	if (me->can_improve_skill("staff"))
		me->improve_skill("staff", 120000);
	me->set("can_perform/dagou-bang/wugou", 1);
	return 1;
}

mixed ask_bang()
{
	object me;
	object ob;
	object owner;

	me = this_player();

	if (me->query("family/family_name") != "ؤ��")
		return "������������ؤ�����֮�������������ʲô��";

	if (me->query("family/master_id") != query("id"))
		return "ֻ���ҵĵ��Ӳ����������ȣ��㻹����ذɡ�";

	ob = find_object(LVYU_ZHANG);
	if (! ob) ob = load_object(LVYU_ZHANG);
	owner = environment(ob);
	while (owner)
	{
		if (owner->is_character() || ! environment(owner))
			break;
		owner = environment(owner);
	}

	if (owner == me)
		return "�����Ȳ������������ô����ô�����������أ�";

	if (objectp(owner) && owner != this_object())
	{
		if (! owner->is_character())
			return "���Ѿ����������Ѿ����ȥ�ˡ�";

		if (owner->query("family/master_id") == query("id"))
			return "������������" + owner->query("name") +
			       "���У���Ҫ���þ�ȥ�����ɡ�";
		else
			return "��������������" + owner->query("name") +
			       "���У���ȥ�����һ����ɡ�";
	}

	ob->move(this_object());
	message_vision("$N���ͷ�������ã�������������Ҫ����һЩ��"
		       "����������飡��\n", this_object(), me);
	command("give lvyu zhang to " + me->query("id"));
	ob->start_borrowing();
	return 1;
}

void unconcious()
{
	die();
}
