// zhenwu_neck.c

#include <ansi.h>
#include <armor.h>

inherit NECK;

string do_wear();

void create()
{
	set_name(HIR "�����令��" NOR, ({"zhenwu neck"}));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����������[�����а]������\n");
		set("material", "neck");    //����
		set("armor_prop/armor", 20);  //����
		set("armor_prop/warm", 1);   //��ů
	       set("value", 10000000);   //��ֵ
		 set("material", "crimson gold");  //ԭ��
		set("wear_msg", (: do_wear :));  //װ����Ϣ
		set("icon","05085");
		  set("suit_point",500);
       //---------------------------------------------------------------
	      //��װ����
		 set("suit",HIR"�����а"NOR);  //��װ����
		set("suit_lvl",5);	     //��װ�ȼ�
		set("suit_count",6);	   //��װ��������
	      //��װ������
		set("suit_mod/arrmor","���䷨��");
		set("suit_mod/finger","�����ָ");
		set("suit_mod/sword","�����а��");
		set("suit_mod/hands","��������");
		set("suit_mod/head","����ͷ��");
		set("suit_mod/neck","���令��");
		set("suit_mod/pants","����ȹ��");			     
	    //��װȫ�������츳Ч��  //����һ�����ǵڶ������ԣ�����
		set("suit_eff/dex",3);      //����
		set("suit_eff/con",4);      // ��� 
		set("suit_eff/int",5);      //����  
		set("suit_eff/str",6);      //    һ��  
	       //��װȫ�����Ӽ���Ч��   
		set("suit_eff_skill/taiji-jian",10);   //һ��
		set("suit_eff_skill/taiji-quan",10); 
		set("suit_eff_skill/taoism",10);	   
       //---------------------------------------------------------------
	}
	setup();
}

string do_wear()
{
	object me;
	string msg;
	int per;

	me = this_player();
	per = me->query("per");
	if (me->query("gender") == "Ů��")
	{
		if (per >= 30)
			msg = HIC "$N" HIC "���Ὣһ��$n" HIC "������ǰ����̬����֮����\n";
		else if (per >= 25)
			msg = HIG "$N" HIG "��$n" HIG "չ����������ǰ��\n";
		else if (per >= 20)
			msg = YEL "$N" YEL "��$n" YEL "������ǰ�����������ӡ�\n";
		else    msg = YEL "$N" YEL "ë��ë�ŵİ�$n" YEL "������ǰ��\n";
	} else
	{
		if (per >= 30)
			msg = HIC "$N" HIC "����һ�ӣ���$n" HIC "������ǰ����������֮����\n";
		else if (per >= 25)
			msg = HIG "$N" HIG "��$n" HIG "չ����������ǰ��\n";
		else if (per >= 20)
			msg = YEL "$N" YEL "��$n" YEL "������ǰ�����˳��½ǣ����������ӡ�\n";
		else    msg = YEL "$N" YEL "ë��ë�ŵİ�$n" YEL "������ǰ�����������\n";
	}
	return msg;
}

int query_autoload()
{
	return 1;
}
