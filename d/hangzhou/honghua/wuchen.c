#include <ansi.h>
inherit NPC;

void create()
{
	set_name("�޳�����", ({"wuchen daozhang", "wuchen", "daozhang"}));
	set("title", HIR "�컨�������" NOR);
	set("nickname", HIW "׷�������" NOR );
	set("gender", "����");
	set("age", 52);
	set("long", 
"������ʱ�켣���֣��ٸ���ƶ�������������ް����书��ǿ�������ֵ����ڣ��ٸ��κ������á���һ��������һλ�ټ�С"
"�㣬��Ȼ�������صİ�����������λС��ȴ���޳���û���ģ����˸��׽�����һ��ҹ���޳�͵͵������֮ʱ����С��˵���������ȫ�Ǽ�"
"�⣬û�����ġ����޳���Ȼ���ķ��䡣��С��������������˰��������Ļ�������˵�������ô��������һ�Σ��ҿɲ�������Ҫ������"
"���ң��Ͱ���һ���ְ������ҡ����������۰����ţ�Ҳ����Ҽ�į�µ������޳�һ�ﲻ������İν����Լ�����ۿ���������С��¥��"
"����������ٲһ����ӿ�˳������޳���ʹ���ڵأ����ﻹ�ֿܵ����޳����µ��ֵ��Ǵ��Ⱥ�������Ƴǳأ������ȳ����ְ�С��ȫ"
"�Ҷ�׽�����������䡣������Ϊ�޳����ǰ����Ƕ�ɱ�ˣ�����Ҫ����С�������ӡ���֪������С�㣬�ĳ�һ�������˰����ͼ��˶����ˣ�"
"�Լ���ҹ�����뿪���ǵط����Ļ��������ʹ˳������˵��ˡ�����Ȼ���˼ң����Ǳ������ƣ����Ǻ������������������컨���ϵ�������ͤ��������˸��֡�\n");
	set("attitude", "peaceful");
	set("class", "taoist");
	set("per", 21);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

	set("qi", 3800);
	set("max_qi", 3800);
	set("jing", 3000);
	set("max_jing", 3000);
	set("neili", 5000);
	set("max_neili", 5000);
	set("jiali", 150);

	set("combat_exp", 2500000);

	set_skill("force", 250);
	set_skill("bibo-shengong", 250);
	set_skill("unarmed", 250);
	set_skill("lianhuan-mizongtui", 250);
	set_skill("dodge", 250);
	set_skill("zhuihun-jian", 250);
	set_skill("parry", 250);
	set_skill("sword", 250);

	map_skill("force"  , "bibo-shengong");
	map_skill("unarmed", "lianhuan-mizongtui");
	map_skill("dodge"  , "lianhuan-mizongtui");
	map_skill("parry"  , "zhuihun-jian");
	map_skill("sword"  , "zhuihun-jian");

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "sword.zhu" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}) );
	setup();
	
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/greyrobe")->wear();
    
}

