// miejue.c ���ʦ̫
// Modified by That Oct.1997

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

#include <ansi.h>
#include "emei.h"

string ask_for_quit();
mixed ask_hui();

mixed ask_skill1();
mixed ask_skill2();

void create()
{
	set_name("���ʦ̫", ({ "miejue shitai","miejue","shitai"}));
	set("long", "���Ƕ����ɵĵ��������ӣ����ζ����������ˡ�\n");
	set("gender", "Ů��");
	set("age", 62);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("no_get", 1);
	set("class", "bonze");
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "sword.mie" :),
	}) );
	set("inquiry",([
		"���"  : "Ҫ����Ҿ�����",
		"����"  : "Ҫ����Ҿ�����",
		"����"  : (: ask_for_quit :),
		"����"  : (: ask_hui :),
		"����"  : (: ask_hui :),
		"�ط����" : (: ask_hui :),
		"�ƺ�����" : (: ask_skill1 :),
		"�������" : (: ask_skill2 :),
	]));

	set("str", 29);
	set("int", 35);
	set("con", 31);
	set("dex", 30);

	set("max_qi", 4500);
	set("max_jing", 2200);
	set("neili", 6000);
	set("max_neili", 6000);
	set("jingli", 1200);
	set("max_jingli", 1200);

	set("combat_exp", 1850000);
	set_skill("persuading", 160);
	set_skill("throwing", 210);
	set_skill("force", 220);
	set_skill("dodge", 200);
	set_skill("finger", 190);
	set_skill("parry", 220);
	set_skill("strike", 190);
	set_skill("sword", 220);
	set_skill("blade", 200);
	set_skill("literate", 120);
	set_skill("mahayana", 220);
	set_skill("buddhism", 210);
	set_skill("jinding-zhang", 190);
	set_skill("tiangang-zhi", 190);
	set_skill("huifeng-jian", 220);
	set_skill("yanxing-dao", 200);
	set_skill("zhutian-bu", 200);
	set_skill("emei-xinfa", 220);
	set_skill("linji-zhuang", 220);
	set_skill("piaoxue-zhang", 220);

	map_skill("force", "linji-zhuang");
	map_skill("finger", "tiangang-zhi");
	map_skill("dodge", "zhutian-bu");
	map_skill("strike", "jinding-zhang");
	map_skill("sword", "huifeng-jian");
	map_skill("blade", "yanxing-dao");
	map_skill("parry", "huifeng-jian");

	prepare_skill("strike", "jinding-zhang");
	prepare_skill("finger", "tiangang-zhi");

	create_family("������", 3, "������");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.mie" :),
		(: perform_action, "sword.hui" :),
		(: perform_action, "finger.lingkong" :),
		(: perform_action, "strike.bashi" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	setup();

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/city/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
	string name;

	if (! permit_recruit(ob))
		return;

	if ((int)ob->query("shen") < 15000)
	{
		command("say " + RANK_D->query_respect(ob) +
			"������������֮������̫�٣�ʵ����̫�٣�");
		return;
	}

	if ((int)ob->query_skill("mahayana", 1) < 100)
	{
		command("say ���˷𷨵���Ϊ�����У��úø������");
		return;
	}

	if ((int)ob->query_skill("emei-xinfa",1) < 100)
	{
		command("say ��ô���£������ڹ��ķ�����ôѧ�ģ��úø�������ȥ��");
		return;
	}

	command("say �ðɣ��Ҿ��������ˡ�");
	command("say �Ժ���Ҫ��Ϊʦһ���������µĶ���ͳͳɱ�⣡");
	command("recruit " + ob->query("id"));

	name = "��" + ob->name(1)[2..<1];
	ob->set_name(name);
}

int recognize_apprentice(object me, string skill)
{
	if (me->query("family/family_name") == "������" &&
	    skill == "mahayana")
		return 1;
	return 0;
	
}

string ask_for_quit()
{
	object me;
	me = this_player();

	if (me->query("family/family_name") != "������")
		return "����ʲô�ˣ��ܵ����������ң�\n";

	if( (string)me->query("class") != "bonze" )
		return "�����ӷ��㱾���׼��ˣ���̸���ף�\n";

	me->set_temp("pending/quit_bonze", 1);
	command("heng");
	command("say ���ף��ã���������Ƕ����ɣ��ұ������㻹��ȥ�ɣ�\n");
	return "��úõĸ��Ұ����������Ժ�����ħ�������������Ӳ�������\n";
}

mixed ask_hui()
{
	object me;

	me = this_player();
	if (me->query("can_perform/huifeng-jian/hui"))
		return "���Լ��úö�������������ħ�Ϳ�������Щ���ˣ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_rude(me) +
		       "���������ģ�����ҹ�����";

	if (me->query_skill("linji-zhuang", 1) < 100)
		return "����ټ�ʮ��ׯ����̫ǳ������ʹ����ط���������еľ���֮����";

	if (me->query_skill("huifeng-jian", 1) < 120)
		return "��ط����������δ�����þ��������������е�΢��֮����";

	if (me->query("shen") < 30000)
		return "�ߺߣ�������������������Ļ����Ĳ�����������";

	message_vision(HIY "$n" HIY "������������գ�������֣�"
		       "�����૵������Ҷ����ɺ�����ˣ�������ˣ���\n"
		       "���˰��Σ�$n" HIY "�Żع�������"
		       HIY "��$N" HIY "�������ܵ�˵��Щʲô��"NOR"\n",
		       me, this_object());
	command("say �����ˣ��Ժ����Щ���˲�Ҫ������һ��ɱһ����������ɱһ˫��");
	tell_object(me, HIG "��ѧ���˻ط�������ľ�����"NOR"\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 160000);

	if (me->can_improve_skill("huifeng-jian"))
		me->improve_skill("huifeng-jian", 160000);
	if (me->can_improve_skill("huifeng-jian"))
		me->improve_skill("huifeng-jian", 160000);
	if (me->can_improve_skill("huifeng-jian"))
		me->improve_skill("huifeng-jian", 160000);
	if (me->can_improve_skill("huifeng-jian"))
		me->improve_skill("huifeng-jian", 160000);
	if (me->can_improve_skill("huifeng-jian"))
		me->improve_skill("huifeng-jian", 160000);

	me->set("can_perform/huifeng-jian/hui", 1);
	return 1;
}

mixed ask_skill1()
{
	object me;

	me = this_player();
	if (me->query("can_perform/piaoxue-zhang/yun"))
		return "��һ���Ҳ����Ѿ������������𣿻���ʲô�������Լ���ȥ���ɡ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return "�������������������֪���´���������";

	if (me->query("family/master_id") != query("id"))
		return "ֻ���ҵĵ��Ӳ���ѧϰ���У��㻹���߰ɡ�";

	if (me->query_skill("piaoxue-zhang", 1) < 1)
		return "����Ʈѩ�����ƶ�ûѧ����̸ʲô���п��ԣ�";

	if (me->query_skill("force") < 200)
		return "����ڹ�����̫ǳ������ѧ������һ�С�";

	if (me->query("max_neili") < 2000)
		return "�����������̫ǳ������ѧ������һ�С�";

	if (me->query_skill("piaoxue-zhang", 1) < 150)
		return "���Ʈѩ�����ƻ��δ��������ѧ������һ�С�";

	if (me->query("shen") < 40000)
		return "��������������黹���ò���������ʱ�����ܴ�����С�";

	message_sort(HIY "\n$n" HIY "΢΢һЦ����$N" HIY "˵��������Ȼ����"
		     "�⹦���Ѵ�����˾��磬Ҳ��������ƽʱ��һ�����ࡣ����"
		     "�ұ㴫����У�ϣ���պ��ܽ��Ҷ����ɷ����󡣡�˵�꣬"
		     "$n" HIY "��$N" HIY "������ǰ����$N" HIY "��������ϸ˵"
		     "���á�"NOR"\n", me, this_object());

	command("nod");
	command("say �ղ�����˵���㶼�������𣿼����˾���ȥ���ɡ�");
	tell_object(me, HIC "��ѧ���ˡ��ƺ����ơ���"NOR"\n");

	if (me->can_improve_skill("strike"))
		me->improve_skill("strike", 1500000);
	if (me->can_improve_skill("piaoxue-zhang"))
		me->improve_skill("piaoxue-zhang", 1500000);
	me->improve_skill("martial-cognize", 1500000);
	me->set("can_perform/piaoxue-zhang/yun", 1);
	//me->add("gongxian", -1800);
	return 1;
}

mixed ask_skill2()
{
	object me;

	me = this_player();
	if (me->query("can_perform/piaoxue-zhang/zhao"))
		return "��һ���Ҳ����Ѿ������������𣿻���ʲô�������Լ���ȥ���ɡ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return "�������������������֪���´���������";

	if (me->query("family/master_id") != query("id"))
		return "ֻ���ҵĵ��Ӳ���ѧϰ���У��㻹���߰ɡ�";

	if (me->query_skill("piaoxue-zhang", 1) < 1)
		return "����Ʈѩ�����ƶ�ûѧ����̸ʲô���п��ԣ�";

	if (me->query_skill("force") < 300)
		return "����ڹ�����̫ǳ������ѧ������һ�С�";

	if (me->query("max_neili") < 3500)
		return "�����������̫ǳ������ѧ������һ�С�";

	if (me->query_skill("piaoxue-zhang", 1) < 180)
		return "���Ʈѩ�����ƻ��δ��������ѧ������һ�С�";

	if (me->query("shen") < 40000)
		return "��������������黹���ò���������ʱ�����ܴ�����С�";

	message_sort(HIY "\n$n" HIY "����������$N" HIY "��ͷ��˵��������"
		     "�ɣ��ѵ���������ģ������Ҿͽ�������ʾһ�飬�ɵÿ�"
		     "���ˣ����������䣬ֻ��$n" HIY "�����ھ������������"
		     "����ž���죬�����Ѫ��ɷ�Ǿ��ˡ��漴$n" HIY "һ����"
		     "�ȣ�˫��Я����������֮��������ǰ�ĳ�����ʱֻ������"
		     "�ꡱһ�����죬ǰ���±�һ����ڴֵ�����Ӧ�����ϣ���"
		     "֦��������δ������ǰ�ַɳ����ɣ���ŵ�����ɽ��֮��"
		     "������������ɽ���»��������ڶ���Ⱥɽ�лص��˺�һ"
		     "�����ʧ������$n" HIY "΢΢һЦ������һ������������"
		     "���ھ�����$N" HIY "��ȥ����$N" HIY "���ѿ���Ŀ�ɿ�"
		     "����"NOR"\n", me, this_object());

	command("say ��������ȥ��һ��Ҫ�ڼ���ϰ�����ܷ��ӳ�����������");
	tell_object(me, HIC "��ѧ���ˡ�������ա���"NOR"\n");

	if (me->can_improve_skill("strike"))
		me->improve_skill("strike", 1500000);
	if (me->can_improve_skill("piaoxue-zhang"))
		me->improve_skill("piaoxue-zhang", 1500000);
	me->improve_skill("martial-cognize", 1500000);
	me->set("can_perform/piaoxue-zhang/zhao", 1);
	//me->add("gongxian", -2200);
	return 1;
}

void unconcious()
{
	die();
}
