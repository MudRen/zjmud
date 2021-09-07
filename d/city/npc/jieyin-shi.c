// city/npc/jieyin-shi.c
inherit NPC;
string do_fly() ;
void create()
{
	set_name("���ɽ���", ({ "jieyin shi"}));	
	set("gender", "Ů��");
	set("age", 20);
	set("per", 30);
	set("con", 30);
	set("int", 30);
	set("level", 20);
	set("icon","00964");
	set("dex", 30);
	set("str", 30);
	set("long","�������ɵĽ���ʹ�ߣ��������ֻ����ɳ�Ա�����������ɣ�����\n");
	set_skill("unarmed", 100);
	set_temp("apply/damage", 50);
	set("inquiry", ([
		"���ɽ���": (:do_fly:),  
	]) );
	set("combat_exp", 500000);
	set("attitude", "friendly");	
	setup();
	carry_object(__DIR__"cloth/feature")->wear();
}

void init()
{
	add_action("fly","fly");
}

string do_fly()
{
	write(ZJOBLONG"�ٺ٣��ҿ��԰�����ٵ���������ɣ�\n"
		ZJOBACTS2+ZJMENUF(3,3,8,30)+
		"�䵱����:fly wudang"ZJSEP
		"��üɽ��:fly emei"ZJSEP
		"����ɽ��:fly shaolin"ZJSEP
		"��ɽ���:fly huashan"ZJSEP
		"��ɽ����:fly xingxiu"ZJSEP
		"��ң����:fly xiaoyao"ZJSEP
		"��Ĺ�ݵ�:fly gumu"ZJSEP
		"����ɽ��:fly quanzhen"ZJSEP
		"ѩɽ��ǰ:fly xueshan"ZJSEP
		"Ѫ����ǰ:fly xuedao"ZJSEP
		"��ţ���:fly wuguan\n");
		return "������������";
}
int fly(string arg)
{
	object me=this_player();
	write("�ٺ٣��Ǿ����Ҿ�����һ�̰ɣ�����\n");
	write(HIY" ���ɽ���ʹ���ó���һ�״��ڣ�һ��ץס�㣬���˽�ȥ����������"NOR"\n");
	write(HIG" ~��~��һ���������� < ��һ��������� > ��������"NOR"\n");
	write(HIB"........ϵͳ����Ĭ����3����........."NOR"\n");
	if (arg=="wudang") me->move("/d/wudang/slxl1");	//�䵱����
	else if (arg=="emei") me->move("/d/emei/bgsgate");	//��üɽ��
	else if (arg=="shaolin") me->move("/d/shaolin/shijie1");	//����ɽ��
	else if (arg=="huashan") me->move("/d/village/eexit");	//��ɽ���
	else if (arg=="lingjiu") me->move("/d/xingxiu/shanjiao");	//��ɽɽ��
	else if (arg=="xingxiu") me->move("/d/xingxiu/shanjiao");	//��ɽɽ��
	else if (arg=="xiaoyao") me->move("/d/xiaoyao/shulin1");	//��ң����
	else if (arg=="gumu") me->move("/d/gumu/caodi");	  //��Ĺ�ݵ�
	else if (arg=="quanzhen") me->move("/d/gumu/zhufeng");	  //����ɽ����
	else if (arg=="xueshan") me->move("/d/xuedao/nroad4");	//ѩɽ��
	else if (arg=="xuedao") me->move("/d/xuedao/wangyougu");	//Ѫ����,���ǹ�
	else if (arg=="wuguan") me->move("/d/city3/wuguan");	//��ţ���
	else write(HIR"\n������û������ɣ���Ҫȥ�Ǹ�����"NOR"\n");
	return 1;
}
