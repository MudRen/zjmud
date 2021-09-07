// liang.c

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include <ansi.h>

void kicking(object ob);

void create()
{
	set_name("������", ({"liang zhanglao", "liang", "zhanglao"}));
	set("title", "ؤ��Ŵ�����");
	set("nickname", "��������");
	set("gender", "����");
	set("age", 55);
	set("long", 
		"��������ؤ�������ã��书��ߵĳ��ϣ��������������Ѿá�"
		"ؤ���书������ǿ������������һ�����٣������������ϡ�\n");

	set("attitude", "peaceful");
	set("class", "beggar");
	set("no_get", 1);
	
	set("str", 28);
	set("int", 24);
	set("con", 24);
	set("dex", 25);

	set("qi", 3000);
	set("max_qi", 3000);
	set("jing", 1500);
	set("max_jing", 1500);
	set("neili", 4800);
	set("max_neili", 4800);
	set("jiali", 100);
	
	set("combat_exp", 1200000);
	
	set_skill("force", 195);
	set_skill("jiaohua-neigong", 195);
	set_skill("unarmed", 180);
	set_skill("changquan", 180);
	set_skill("strike", 170);
	set_skill("xiaoyaoyou", 170);
	set_skill("dodge", 170);
	set_skill("feiyan-zoubi", 170);
	set_skill("parry", 190);
	set_skill("staff", 170);
	set_skill("jiaohua-bangfa", 170);
	set_skill("begging", 80);
	set_skill("checking", 150);
	set_skill("training", 120);
	
	map_skill("force", "jiahua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("strike", "xiaoyaoyou");
	map_skill("staff", "jiaohua-bangfa");
	map_skill("dodge", "feiyan-zoubi");

	create_family("ؤ��", 18, "�Ŵ�����");
	setup();
}

void init()
{
	object ob;
	mapping myfam;
	
	::init();

	if (! stringp(query("startroom")) ||
	    find_object(query("startroom")) != environment())
		return;

	if (interactive(ob = this_player()) &&
	    ! wizardp(ob) && ! is_fighting() && living(this_object()))
	{
		myfam = (mapping)ob->query("family");
		if (! myfam || myfam["family_name"] != "ؤ��")
		{
			message_vision(HIW "�����Ͽ���$N�����������һ�����㲻��ؤ����ӣ����ҹ���ȥ��"NOR"\n",
				       ob);
			kicking(ob);
		}
	}
}

void kicking(object ob)
{
	if (!ob || environment(ob) != environment()) return;

	message_vision(HIC "ֻ��������һ��ǡ������$N��ƨ��" + "��$Nһ�������ͷ��˳�ȥ��"NOR"\n", ob);

	ob->move("/d/gaibang/inhole");
	message("vision","ֻ����ƹ����һ����" + ob->query("name") +
		"��С������˳�����\n", environment(ob), ob);
}

void attempt_apprentice(object ob)
{
	if (ob->query("detach/ؤ��") || ob->query("betrayer/ؤ��"))
	{
		command("say ��������Ի�ͷ�ݣ�û�ţ�");
		return 0;
	}

	if (ob->query("betrayer/times"))
	{
		command("say ����ؤ����Ȼ�ǽл��ӣ���������������·����������ʦ֮ͽ�ģ�");
		return 0;
	}

	if (ob->query("family/family_name") && ob->query("family/family_name") != "ؤ��")
	{
		command("say �٣����Ȼ�Ѿ�������ʦָ�㣬��������ؤ���ʲô��");
		return 0;
	}

	if ((int)ob->query_str() < 30)
	{
		command("say ����ؤ�������һ���Ը���Ϊ����" + 
		RANK_D->query_respect(ob) + "����̫�����ƺ�����ѧؤ��Ĺ���");
		return;
	}

	if (ob->query_skill("force") < 150)
	{
		command("say ����ڹ���򻹲��У��Ⱥͱ��ʦ��ѧϰ�ɡ�");
		return;
	}

	command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) + "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
	command("recruit " + ob->query("id"));
}

int recognize_apprentice(object me)
{
	if (me->query("family/family_name") != query("family/family_name"))
		return 0;

	if (me->query("beggarlvl") < 9)
		return 0;

	return 1;
}

void unconcious()
{
	die();
}
