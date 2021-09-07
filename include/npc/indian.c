// indian.c ӡ��

#include "name.h"

mapping ma_sname = ([
	"��"   : "sa",
	"��"   : "la",
	"��"   : "a",
	"��"   : "wu",
	"����" : "abi",
	"�Ǳ�" : "yabi",
	"����" : "youli",
	"�̢" : "kanda",
	"˼��" : "sige",
	"���" : "hengda",
	"�ڸ�" : "tengge",
	"���" : "foda",
	"����" : "sige",
	"ɳ��" : "shage", 
	"��³" : "palu",
	"����" : "kena",
	"Ħ��" : "moli",
	"����" : "ganya",
	"������" : "mamanke",
	"˹��̢" : "sikanda",
	"��˹³" : "masilu",
	"������" : "mankeya",
]);

mapping ma_pname = ([
	"Ĳ»" : "molu",
	"Ħ��" : "moke",
	"����" : "mandu",
	"����" : "youna",
	"ռ��" : "zhanke",
	"�п�" : "shangke",
	"����" : "fate",
	"����" : "xiuli",
	"껸�" : "haoge",
	"��ķ" : "damu",
	"��ķ" : "limu",
	"˹��" : "simu",
	"����" : "hante",
	"��ô" : "hanme",
	"��ķ" : "tamu",
	"��ķ" : "enmu",
	"����" : "haimu",
	"��ķ" : "ganmu",
	"˹����" : "simate",
	"������" : "hannali",
	"������" : "simanda",
	"������" : "yalida",
	"˹����" : "simanka",
	"���´�" : "feimuda",
]);

void generate_in_name(object ob)
{
	string name, sname, pname, id1, id2;
	string *ks, *kp;

	ks = keys(ma_sname);
	kp = keys(ma_pname);
	sname = ks[random(sizeof(ks))];
	pname = kp[random(sizeof(kp))];
	id1 = ma_sname[sname];
	id2 = ma_pname[pname];	
	name = sname + pname;

	if (ob) ob->set_name(name, ({ id1 + " " + id2, id1, id2 }));
}

