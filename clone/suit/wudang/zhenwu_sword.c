#pragma save_binary
#include <weapon.h> 
#include <ansi.h>

inherit SWORD;


void create()
{
	set_name(HIR"�������а��"NOR, ({"zhenwu sword"}));
	set_weight(5000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ�Ѳ�֪��ʲô�������Ľ����������ĵĹ�â\n");
		set("value", 20000000);   //��ֵ
		 set("material", "crimson gold");  //ԭ��
		set("wield_msg",
"$N��ৡ���һ�����һ��$n�������У�\n");
		set("unwield_msg",
"$N�����е�$n�������䣬���¶��һ˿Ц�⣮\n");
	 set("weapon_prop/int", 2);
	 set("icon","05093");
	    set("suit_point",1000);
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
	init_sword(80);
	setup();
}

int query_autoload()
{
	return 1;
}

