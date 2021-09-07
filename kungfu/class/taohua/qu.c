// qu.c
#include <ansi.h>
#include "taohua.h"

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name( "�����" ,({ "qu lingfeng", "qu" }));
	set("gender", "����");
	set("age", 46);
	set("long",
	    "������ǻ�ҩʦ�Ĵ�ͽ�ܣ�Ҳ�ǻ�ҩʦ������ͽ�������Ի�ҩʦһ��\n"
	    "���Ĺ������������Ը�Ź֣�������ʦ����а����\n"
	    "�������޳�����òӢ��������ƮƮ������������\n");
	set("attitude", "peaceful");
	set("class", "scholar");
	set("str", 24);
	set("int", 31);
	set("con", 28);
	set("dex", 22);
	set("chat_chance", 1);
	set("chat_msg", ({
	    "�����˵������ʦ���۰�Сʦ�ã�������⬼�һֱ��Сʦ�ô��š���\n",
	    "��������������˵����������һ����ˣ����򵥣���\n",
	}));
	set("max_qi", 4200);
	set("max_jing", 2100);
	set("neili", 4400);
	set("max_neili", 4400);
	set("jiali", 50);
	set("shen_type", 0);

	set("combat_exp", 1200000);
	set_skill("force", 160);	     // �����ڹ�
	set_skill("luoying-xinfa", 160);     // ��Ӣ�ķ�
	set_skill("unarmed", 150);	   // ����ȭ��
	set_skill("xuanfeng-leg", 150);      // ����ɨҶ��
	set_skill("strike", 140);	    // �����Ʒ�
	set_skill("luoying-shenzhang", 140); // ��Ӣ����
	set_skill("dodge", 170);	     // ��������
	set_skill("anying-fuxiang", 170);    // ��Ӱ����
	set_skill("parry", 150);	     // �����м�
	set_skill("sword", 150);	     // ��������
	set_skill("luoying-shenjian", 150);  // ��Ӣ��
	set_skill("qimen-wuxing", 150);      // ��������
	set_skill("literate", 180);	  // ����ʶ��

	map_skill("force"  , "luoying-xinfa");
	map_skill("unarmed", "xuanfeng-leg");
	map_skill("strike" , "luoying-zhang");
	map_skill("dodge"  , "anying-fuxiang");
	map_skill("parry"  , "luoying-shenjian");
	map_skill("sword"  , "luoying-shenjian");

	prepare_skill("unarmed", "xuanfeng-leg");
	prepare_skill("strike" , "luoying-zhang");

	create_family("�һ���", 2, "����");

	set("inquiry", ([
	   "�һ���":   "��������һ������������Ǳ��ɵ��ӣ�Ҫ���һ���",
	   "�һ���":   "���Ͼ����ˡ�",
	   "��а":     "��ʦ�˳ƶ�а���Ǻǡ�",
	   "����":     "ŷ���������ʦ���������ĸ��֣��˳��϶��",
	   "�ϵ�":     "����ʦ˵����ү���ڳ��ҵ��˺��У�����һ�ơ�",
	   "��ؤ":     "��ؤ���߹���ؤ��������������ݳ��⡣",
	   "����":     "����ʦ���İ�Ů��",
	   "��ҩʦ":   "��Ҫ�ݷü�ʦ��"
	]));
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

