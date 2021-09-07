// japanese name

#include "name.h"

mapping jp_sname = ([
	"��ľ" : "baimu",
	"����" : "beitiao",
	"����" : "chuandao",
	"����" : "cunzheng",
	"��"   : "dong",
	"����" : "dongtiao",
	"�᳼" : "fengchen",
	"����" : "fubu",
	"����" : "gaoqiao",
	"����" : "heitian",
	"�ƾ�" : "jiujing",
	"����" : "laichuan",
	"ë��" : "maoli",
	"ľ��" : "muxia",
	"��ľ" : "qingmu",
	"����" : "qiteng",
	"����" : "songxia",
	"ɽ��" : "shanben",
	"��ڣ" : "shouzhong",
	"����" : "tianzhong",
	"����" : "tengze",
	"����" : "tufei",
	"�乬" : "wugong",
	"Сɽ" : "xiaoshan",
	"С��" : "xiaolin",
	"СԨ" : "xiaoyuan",
	"ϸ��" : "xichuan",
	"����" : "yitian",
	"֯��" : "zhitian",
	"����" : "zhennei",
	"����" : "zhongtian",
	"����" : "zhuzhong",
	"����" : "zuishang",
]);

mapping jp_pname = ([
	"an"   : "��",
	"ao"   : "����",
	"bang" : "��",
	"bei"  : "��������",
	"biao" : "��",
	"cao"  : "��",
	"cang" : "�Բ�",
	"chang": "��",
	"chi"  : "�ٳ�",
	"ci"   : "�˴�",
	"dong" : "��",
	"fa"   : "��",
	"fan"  : "��ެ",
	"fang" : "��",
	"feng" : "�����",
	"fu"   : "���",
	"gao"  : "��",
	"hao"  : "�",
	"hong" : "��",
	"hui"  : "��",
	"ji"   : "�����Ǽͼ��̼������",
	"jian" : "������",
	"ke"   : "��",
	"lang" : "����",
	"li"   : "��������",
	"lin"  : "��",
	"mao"  : "�",
	"nan"  : "��",
	"qian" : "ǫǧ",
	"qin"  : "��",
	"qing" : "��",
	"ran"  : "Ȼ",
	"ren"  : "��������",
	"shang": "��",
	"shen" : "��������",
	"shi"  : "ʦʷʯʱʮ��ʿ��",
	"si"   : "˼˹˾",
	"tian" : "������",
	"wan"  : "��",
	"wei"  : "��΢ΰά��",
	"wu"   : "��������",
	"xi"   : "ϯϴϦ",
	"xiao" : "����",
	"xiong": "��",
	"yang" : "������",
	"yi"   : "����������������������ܲ",
	"yin"  : "����",
	"ying" : "ӳӢӰ",
	"you"  : "����",
	"yu"   : "����Ԥ",
	"zhi"  : "��֪��־ֱ��",
	"zhong": "��",
	"zhou" : "������",
	"zhu"  : "����",
	"zhuo" : "׿ߪ",
	"zi"   : "��",
	"zong" : "��",
	"zuo"  : "��",
]);

mapping jp_number = ([
	"tai" : "̫",
	"ci"  : "��",
	"san" : "��",
	"si"  : "��",
	"wu"  : "��",
]);

void generate_jp_name(object ob)
{
	string name, pname1, pname2, id, id1, id2;
	string *r, *ks;

	ks = keys(jp_sname);
	name = ks[random(sizeof(ks))];
	id = jp_sname[name];

	r = select_a(jp_pname, id);
	id1 = r[0];
	pname1 = r[1];

	if (random(2))
	{
		r = select_a(jp_pname, id);
		id2 = r[0];
		pname2 = r[1];
	} else
	{
		r = select_a(jp_number, id);
		id2 = r[0];
		pname2 = r[1];
		if (random(3))
		{
			pname1 = pname2 + "��";
			id1    = id2 + "lang";
		} else
		{
			pname1 += pname2;
			id1    += id2;
		}
		pname2 = "";
		id2    = "";
	}

	switch (random(2))
	{
	case 0:
		id2 = id1 + id2;
		id1 = id;
		id += " " + id2;
		name += pname1 + pname2;
		break;
	case 1:
		id2 = id1;
		id1 = id;
		id += " " + id2;
		name += pname1;
	}

	if (ob) ob->set_name(name, ({ id, id1, id2 }));
}
