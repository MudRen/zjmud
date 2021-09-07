// shou.c
#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;

void create()
{
	set_name("��ͷ��", ({ "shou toutuo", "shou" ,"toutuo"}));
	set("title", HIY"������"NOR"�һ���");
	set("nickname",HIR "�ɶ�������" NOR);
	set("long", "��ͷ������氫�������ֵó��棬�����˾ͻ�������һ���󶬹ϡ�\n"
		    "��������Դ��ϵ���һ��ͭ����ۣ����ӷǳ�������\n" );
	set("gender", "����");
	set("age", 44);

	set("str", 26);
	set("int", 18);
	set("con", 31);
	set("dex", 25);

	set("max_qi", 3600);
	set("qi", 3600);
	set("max_jing", 1800);
	set("jing", 1800);
	set("neili", 4200); 
	set("max_neili", 4200);
	set("jiali", 50);
	set("combat_exp", 680000);
	set("shen_type", -1);
	set("attitude", "peaceful");

	set_skill("force", 150);
	set_skill("hand", 150);
	set_skill("strike", 150);
	set_skill("staff", 150);
	set_skill("parry", 150);
	set_skill("dodge", 150);
	set_skill("yixingbu", 150);
	set_skill("shenlong-bashi", 150);
	set_skill("huagu-mianzhang", 150);
	set_skill("shenlong-xinfa", 150);
	set_skill("shedao-qigong", 150);

	map_skill("force", "shenlong-xinfa");
	map_skill("staff", "shedao-qigong");
	map_skill("hand", "shenlong-bashi");
	map_skill("strike", "huagu-mianzhang");
	map_skill("parry", "shenlong-bashi");
	map_skill("dodge", "yixingbu");
	prepare_skill("hand", "shenlong-bashi");
	prepare_skill("strike", "huagu-mianzhang");

	create_family("������", 0, "��ɢ����");

	set_temp("apply/attack", 100);
	set_temp("apply/defense", 100);
	set_temp("apply/armor", 100);
	set_temp("apply/damage", 100);

	set("inquiry", ([
		"������" : "һ�������벻���������̵�(join shenlongjiao).\n",
		"���"   : "һ�������벻���������̵�(join shenlongjiao).\n",
		"�鰲ͨ" : "����Ƣ������,Ҫ�������Ĳźá�\n",
		"����"   : "����Ƣ������,Ҫ�������Ĳźá�\n",
		"�ں�"   : "���겻�ϣ������ɸ����������룡������ʥ��",
	]) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 35);
}

void attempt_apprentice(object ob)
{
	command("say �������ڴ�ү��ǰϹ�Ρ�");
}

