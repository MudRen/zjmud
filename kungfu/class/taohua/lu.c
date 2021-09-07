// lu.c
#include <ansi.h>
#include "taohua.h"

inherit NPC;								    
inherit F_MASTER;

void create()
{
	set_name( "½�˷�" ,({ "lu chengfeng", "lu" }));
	set("gender", "����");
	set("age", 52);
	set("long",
	    "½�˷��ǻ�ҩʦ�ĵ��ĸ�ͽ�ܡ�\n"
	    "�����޽���΢���׷�������Ŀ��࣬˫������\n");
	set("attitude", "friendly");
	set("class", "scholar");
	set("str", 24);
	set("int", 30);
	set("con", 25);
	set("dex", 21);

	set("max_qi", 4000);
	set("max_jing", 2000);
	set("neili", 4200);
	set("max_neili", 4200);
	set("jiali", 50);
	set("shen_type",1);

	set("combat_exp", 1500000);

	set_skill("force", 170);	    // �����ڹ�
	set_skill("luoying-xinfa", 170);    // ��Ӣ�ķ�
	set_skill("unarmed", 160);	  // ����ȭ��
	set_skill("xuanfeng-leg", 160);     // ����ɨҶ��
	set_skill("strike", 160);	   // �����Ʒ�
	set_skill("luoying-shenzhang", 160);// ��Ӣ����
	set_skill("dodge", 150);	    // ��������
	set_skill("anying-fuxiang", 150);   // ��Ӱ����
	set_skill("parry", 160);	    // �����м�
	set_skill("sword", 160);	    // ��������
	set_skill("luoying-shenjian", 160); // ��Ӣ��
	set_skill("literate", 140);	 // ����ʶ��

	map_skill("force"  , "luoying-xinfa");
	map_skill("unarmed", "xuanfeng-leg");
	map_skill("strike" , "luoying-zhang");
	map_skill("dodge"  , "anying-fuxiang");
	map_skill("parry"  , "luoying-shenjian");
	map_skill("sword"  , "luoying-shenjian");

	prepare_skill("unarmed", "xuanfeng-leg");
	prepare_skill("strike" , "luoying-zhang");

	set("jinbing", 10);
	create_family("�һ���", 2, "���� ����ׯ��");

	set("inquiry", ([
	   "�һ���":   "��������һ������������Ǳ��ɵ��ӣ�Ҫ���һ���",
	   "�һ���":   "���Ͼ����ˡ�",
	   "��а":     "��ʦ�˳ƶ�а���Ǻǡ�",
	   "����":     "ŷ���������ʦ���������ĸ��֣��˳��϶��",
	   "�ϵ�":     "����ʦ˵����ү���ڳ��ҵ��˺��У�����һ�ơ�",
	   "��ؤ":     "��ؤ���߹���ؤ��������������ݳ��⡣",
	   "����":     "����ʦ���İ�Ů��",
	   "��ҩʦ":   "��Ҫ�ݷü�ʦ��"
	]) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian");
}

void attempt_apprentice(object ob)
{
	string master;
	if (! permit_recruit(ob))
		return;
	
	if (stringp(master = ob->query_temp("taohua/master")))
	{
		if (master != name())
		{
			command("say ��ʦ���������" + master +
				"��������ô���������ˣ�");
			return;
		}

		command("say �ðɣ���Ȼ��ʦ����Ҿ��������ˣ�����Ҫ�ú������һ����Ĺ�ء�");
		command("recruit " + ob->query("id"));
		ob->delete_temp("taohua/master");
		return;
	}

	if (ob->query("family/master_name") == "��ҩʦ" &&
	    ob->query("family/family_name") == "�һ���")
	{
		command("say ��Ҷ��ǻƵ����ĵ��ӣ���ͱ����Ѱ�����ˡ�");
		return;
	}

	command("shake");
	command("say �ҿɲ���������ͽ���㻹���Ҽ�ʦ�Ƶ����ɣ�");
}

int accept_fight(object ob)
{
	command("wield jian");
	return 1;
}

int accept_object(object who, object ob)
{
	int exp;
	if (query("jinbing") < 0)
	{
		command("say " + RANK_D->query_respect(who) + "�Һ��ۣ����ͷ�������Ͱɡ�");
		return 0;
	}
	if (strsrch(ob->query("name"), "���տ���ͷ­") < 0 &&
	    strsrch(ob->query("name"), "���պ��ҵ�ͷ­") < 0 &&
	    strsrch(ob->query("name"), "ŷ�����ͷ­") < 0 &&
	    strsrch(ob->query("name"), "ŷ���˵�ͷ­") < 0 &&
	    strsrch(ob->query("name"), "��������ͷ­") < 0 &&
	    strsrch(ob->query("name"), "�����̵�ͷ­") < 0 &&
	    strsrch(ob->query("name"), "�������˵�ͷ­") < 0 &&
	    strsrch(ob->query("name"), "ɳͨ���ͷ­") < 0 &&
	    strsrch(ob->query("name"), "��ͨ����ͷ­") < 0 &&
	    strsrch(ob->query("name"), "����յ�ͷ­") < 0 &&
	    strsrch(ob->query("name"), "�����ҵ�ͷ­") < 0 &&
	    strsrch(ob->query("name"), "�����۵�ͷ­") < 0 &&
	    strsrch(ob->query("name"), "Ǯ�ཡ��ͷ­") < 0 &&
	    strsrch(ob->query("name"), "������ͷ­") < 0 &&
	    strsrch(ob->query("name"), "����µ�ͷ­") < 0) 
	{
		command("say ������Щ������ʲô�ã�\n");
		return 0;
	}
	else
	{
		command("say ��������һֱ��ɱ��Щ�𹷣�л������ˡ�");
	}
	exp = 20+random(30);
	add("jinbing", -1);
	tell_object(who,HIW"½�˷罱������\n"+chinese_number(exp)+"��ʵս����"NOR"\n");
	return 1;
}
