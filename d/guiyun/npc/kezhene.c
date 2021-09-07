// kezhene.c
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("�����", ({ "ke zhene", "ke" }));
	set("title", "��������");
	set("nickname", HIM"��������"NOR);
	set("long", "����һ���������ڵ�Ϲ�ӣ���������һ���ִ�����ȡ�ֻ����
������������ɫ�����˵أ������׶�̬֮��\n");
	set("gender", "����");
	set("age", 44);
	set("attitude", "peaceful");
	set("class", "fighter");
	set("shen_type", 1);
	set("per", 12);
	set("str", 28);
	set("int", 28);
	set("con", 28);
	set("dex", 28);
	
	set("max_qi", 2500);
	set("max_jing", 1500);
	set("neili", 3500);
	set("max_neili", 3500);
	set("jiali", 50);
	set("combat_exp", 800000);
	set("score", 12000);

	set_skill("force", 180);
	set_skill("taixuan-gong", 180);
	set_skill("dodge", 180);
	set_skill("lingxu-bu", 180);
	set_skill("unarmed", 180);
	set_skill("changquan", 180);
	set_skill("staff", 180);
	set_skill("xiangmo-zhangfa", 180);
	set_skill("parry", 180);
	set_skill("throwing", 180);
	set_skill("feixing-shu", 180);

	map_skill("force", "taixuan-gong");
	map_skill("unarmed", "changquan");
	map_skill("dodge", "lingxu-bu");
	map_skill("staff", "xiangmo-zhangfa");
	map_skill("parry", "xiangmo-zhangfa");
	map_skill("blade", "feixing-shu");

	set("inquiry", ([
		"����" : "���������ǵĹ�ͽ����\n",
		"��������" : "�����ɲ��ҵ������������ý������и��˺Žн����߹֣�\n",
		"�����߹�" : "�߹�Ҳ����еģ���\n",
		"�𴦻�" : "������������壬�������ӣ�\n",
		"�����" : "����Ϲ���ң���Ҫ���ģ���\n",
		"���"   : "�����Ҷ��ܡ�\n",
		"������"   : "���������ܡ�\n",
		"��ϣ��"   : "�������ĵܡ�\n",
		"�Ű���"   : "��������ܡ�\n",
		"ȫ��"   : "���������ܡ�\n",
		"��СӨ"   : "���������á�\n",
		"÷����"   : "�����ʬ�����Ҵ�磬�˳�һ��Ҫ����\n",
				"��ħ�ȷ�" : "�ٺ٣������ҵĶ��ž��С�\n",
	]));

	setup();
	carry_object("/clone/weapon/gangzhang")->wield();
	carry_object("/clone/misc/cloth")->wear();
}

int recognize_apprentice(object me, string skill)
{
	if (me->query("character") != "�ĺ�����")
	{
		command("say ���ɷ����±����ĺ��������ҿ��㲻�������ˡ�");
		return -1;
	}

	if (me->query("weiwang") < 100000)
	{
		command("say ���Ǵ��������ģ��ڽ�����û���������ˣ������ᴫ�����书��");
		return -1;
	}

	if (skill != "xiangmo-zhangfa")
	{
		command("say ��Щ�ҿɲ�֪�壬��ȥ��һ����ʦ���ɡ�");
		return -1;
	}

	return 1;
}

void unconcious()
{
	die();
}

